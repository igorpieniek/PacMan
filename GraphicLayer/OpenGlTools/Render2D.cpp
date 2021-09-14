#include "Render2D.h"

Render2D& Render2D::instance(){
    static Render2D inst;
    return inst;
}

void Render2D::init(){
    if (!isInitialized) {
        isInitialized = true;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        std::vector<float> vertexBufferData = {
          -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
           0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
           0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
          -0.5f,  0.5f, 0.0f,   1.0f, 0.5f, 1.0f,  0.0f, 1.0f,
        };

        std::vector<unsigned int> indices = {
           0,1,2,   // first triangle
           2,3,0,   // second triangle
        };

        va = std::make_shared<VertexArray>();
        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(3);
        layout.push<float>(2);

        vb = std::make_shared <VertexBuffer>(vertexBufferData);

        va->addBuffer(*vb, layout);

        ib = std::make_shared<IndexBuffer>(indices);

        shader = std::make_shared<Shader>("GraphicLayer/OpenGlTools/shaders/pos2D.vert",
                                          "GraphicLayer/OpenGlTools/shaders/color2D.frag");

        ib->unbind();
        vb->unbind();
    }
}

void Render2D::addToDraw(std::shared_ptr<Texture> text, Transformation& trans){
    textureRender.push_back({ text, trans, false });
}

void Render2D::process(){
    renderer.clear();
    for (auto& textRend : textureRender) {
        //all process, render and draw all elements
        //shader->bind();
        //textRend.text->set();
        textRend.text->bind();
        shader->setUniformMatrix(uniformTransform, textRend.trans.getPointer());
        textRend.isUsed = true;
        renderer.draw(va, ib);
    }
    textureRender.clear();
}
