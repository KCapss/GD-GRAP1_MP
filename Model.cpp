#include "Model.h"
#include "ObjectTextureManager.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model()
{
    //Default option as base class
}

Model::Model(std::string name, ObjectType objType, GLFWwindow* currWindow)
{
	this->name = name;
	this->objType = objType;
    this->window = currWindow;
    

    
    shader = new Shader(this->name);
    //perspCam = new PerspectiveCamera();
    

    if (this->objType != SkyboxObj) {
        loadObj();
        if (this->objType != NoTexture) {
            loadTexture();
        }
        loadBuffer();
    }

}

void Model::retrieveSource(Light* light, PerspectiveCamera* perspCam, OrthographicCamera* orthoCam)
{
    this->light = light;
    this->perspCam = perspCam;
    this->orthoCam = orthoCam;
}

void Model::setInitialPos(glm::vec3 pos)
{
    this->position = pos;
}


void Model::loadObj()
{
    //Iniitalize obj points
    std::string path = ObjectTextureManager::getInstance()->getObjPath(this->name);
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes;
    bool success = tinyobj::LoadObj(&attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str());

    
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        int pos_offset = (vData.vertex_index * 3);
        int normal_offset = (vData.normal_index * 3);

        //For vertex position
        fullVertexData.push_back(  //For X
            attributes.vertices[
                pos_offset
            ]);

        fullVertexData.push_back(  //For y
            attributes.vertices[
                pos_offset + 1
            ]);

        fullVertexData.push_back(  //For z
            attributes.vertices[
                pos_offset + 2
            ]);

        //Normal Map (Contains 3 float)

        fullVertexData.push_back(  //Component A
            attributes.normals[
                normal_offset
            ]);

        fullVertexData.push_back( //Component B
            attributes.normals[
                normal_offset + 1
            ]);

        fullVertexData.push_back(  //Component C
            attributes.normals[
                normal_offset + 2
            ]);

        //UV Coordinate

        fullVertexData.push_back(   // For U
            attributes.texcoords[
                vData.texcoord_index * 2
            ]
        );
        fullVertexData.push_back(   // For V
            attributes.texcoords[
                (vData.texcoord_index * 2) + 1
            ]
        );


    }

    //For Shaders
    shader->initialize();
}


//Might Change due to not teaching the normals yet
void Model::loadTexture()
{
    //Initialize for Texture (JPG)
    int img_width, img_height, colorChannel;
    stbi_set_flip_vertically_on_load(true);

    
    std::string texturePath = ObjectTextureManager::getInstance()->getTexturePath(this->name);
    this->tex_bytes =
        stbi_load(texturePath.c_str(),
            &img_width,
            &img_height,
            &colorChannel,
            0);

    //Generate Texture
    glGenTextures(1, &this->texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB, //RGB since no alpha channel in JPG file
        img_width,
        img_height,
        0,
        GL_RGB, //RGB since no alpha channel in JPG file
        GL_UNSIGNED_BYTE,
        tex_bytes
    );

    //GenerateMipMap for performance
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(this->tex_bytes);
    glEnable(GL_DEPTH_TEST);
}

void Model::loadBuffer()
{
    //Initialize the new buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * fullVertexData.size(),
        fullVertexData.data(),  //Data of the Array
        GL_DYNAMIC_DRAW
    );

    //For Vertex Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );

    GLintptr normPtr = 3 * sizeof(GLfloat);
    GLintptr uvPtr = 6 * sizeof(GLfloat);

    //Normal Pointer
    glVertexAttribPointer(
        1, //Normal
        3, //x,y,z
        GL_FLOAT,
        GL_TRUE,
        8 * sizeof(float),
        (void*)normPtr //Offset from the start
    );

    //UV Map
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)uvPtr //Offset from the start
    );

    if (objType != ObjectType::SkyboxObj) {
        if (objType != ObjectType::NoTexture) {
            glEnableVertexAttribArray(2);  //UV MAP
            glEnableVertexAttribArray(1);  //Normal Map
        }

        glEnableVertexAttribArray(0);  //Vertex Pos
    }
    

    //Bind Everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

glm::vec3 Model::retrieveCamPos()
{
    if (currCam == ActiveCam::Perspective) {
        return this->perspCam->getCameraPos();
    }

    else if (currCam == ActiveCam::Orthographic) {
        return this->orthoCam->getCameraPos();
    }
}

glm::mat4 Model::retrieveCamMat()
{
    if (currCam == ActiveCam::Perspective) {
        return this->perspCam->getViewMatrix();
    }

    else if (currCam == ActiveCam::Orthographic) {
        return this->orthoCam->getViewMatrix();
    }
}

glm::mat4 Model::retrieveCamProj()
{
    if (currCam == ActiveCam::Perspective) {
        return this->perspCam->getProjection();
    }

    else if (currCam == ActiveCam::Orthographic) {
        return this->perspCam->getProjection();
    }
}

void Model::draw()
{
    //Apply Linear Transformation (Default)
    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 transform = glm::translate(identity, this->position);
    transform = glm::scale(transform, glm::vec3(.25f, .25f, .25f)); //default scaling
    //transform = glm::scale(transform, glm::vec3(2.25f, 2.25f, 2.25f)); //default other obj


    glUseProgram(shader->getShaderProg());

    
    shader->transformUpdate(transform);

    shader->projectionUpdate(perspCam->getProjection());
    shader->viewUpdate(perspCam->getViewMatrix());

    if (objType == WithTexture) {
        shader->textureUpdate(texture);
        shader->LightUpdate(light);
        shader->cameraUpdatePos(perspCam->getCameraPos());
    }
    
    glUseProgram(shader->getShaderProg());

    glBindVertexArray(VAO); // Render on the active
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);

    //Retrieve Delta Time Later
}

void Model::deAllocate()
{
    //delete vertex && buffers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
