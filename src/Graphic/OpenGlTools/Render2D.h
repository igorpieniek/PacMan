#pragma once

#include "Transformation.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include <vector>
#include "GL/glew.h"

class Render2D {
public:
	static Render2D& instance();
    void init();
    void addToDraw(std::shared_ptr<Texture> text, Transformation& trans);
    void process();

    void operator=(const Render2D&) = delete;

private:
    Render2D() {
        textureRender.reserve(500);
    };

    struct TextureRenderer {
        std::shared_ptr<Texture> text{};
        Transformation trans{};
        bool isUsed{};
    };

    bool isInitialized = false;
    std::vector<TextureRenderer> textureRender{};
    const char uniformTransform[10] = "transform";

    std::shared_ptr<VertexArray>  va{};
    std::shared_ptr<Shader> shader{};
    std::shared_ptr<IndexBuffer> ib{};
    std::shared_ptr<VertexBuffer> vb{};
    Renderer renderer{};
};

