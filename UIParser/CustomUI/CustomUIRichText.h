/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CUSTOM_UIRICHTEXT_H__
#define __CUSTOM_UIRICHTEXT_H__

#include "ui/UIWidget.h"
#include "cocos2d.h"
#include "CustomUIData.h"
#include "CustomUIInterface.hpp"

class CustomRichText;

class CustomRichElement : public cocos2d::Ref
{
public:
    /**
     *@brief Rich element type.
     */
    enum class Type
    {
        TEXT,
        IMAGE,
        CUSTOM
    };
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     */
    CustomRichElement(){};
    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~CustomRichElement(){};

    
    /**
     * @brief Initialize a rich element with different arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in @see `Color3B`.
     * @param opacity A opacity value in `GLubyte`.
     * @return True if initialize success, false otherwise.
     */
    bool init(int tag, const cocos2d::Color3B& color, GLubyte opacity);

    Type _type;
    int _tag;
    cocos2d::Color3B _color;
    GLubyte _opacity;
    friend class CustomRichText;
};
    
/**
 *@brief Rich element for displaying text.
 */
class CustomRichElementText : public CustomRichElement
{
public:
    
    /**
     *@brief Default constructor.
     * @js ctor
     * @lua new
     */
    CustomRichElementText(){_type = Type::TEXT;};

    
    /**
     *@brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~CustomRichElementText(){};
    
    /**
     * @brief Initialize a RichElementText with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param text Content string.
     * @param fontName Content font name.
     * @param fontSize Content font size.
     * @return True if initialize scucess, false otherwise.
     */
    bool init(int tag, const cocos2d::Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);

    
    /**
     * @brief Create a RichElementText with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param text Content string.
     * @param fontName Content font name.
     * @param fontSize Content font size.
     * @return RichElementText instance.
     */
    static CustomRichElementText* create(int tag, const cocos2d::Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);

    std::string _text;
    std::string _fontName;
    float _fontSize;
    friend class CustomRichText;
    
};

/**
 *@brief Rich element for displaying images.
 */
class CustomRichElementImage : public CustomRichElement
{
public:
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     *
     */
    CustomRichElementImage(){_type = Type::IMAGE;};

    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~CustomRichElementImage(){};

    
    /**
     * @brief Initialize a RichElementImage with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param filePath A image file name.
     * @return True if initialize success, false otherwise.
     */
    bool init(int tag, const cocos2d::Color3B& color, GLubyte opacity, const std::string& filePath);

    
    /**
     * @brief Create a RichElementImage with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param filePath A image file name.
     * @return A RichElementImage instance.
     */
    static CustomRichElementImage* create(int tag, const cocos2d::Color3B& color, GLubyte opacity, const std::string& filePath);

    std::string _filePath;
    cocos2d::Rect _textureRect;
    int _textureType;
    friend class CustomRichText;
};
    
/**
 *@brief Rich element for displaying custom node type.
 */
class CustomRichElementCustomNode : public CustomRichElement
{
public:
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     */
    CustomRichElementCustomNode(){_type = Type::CUSTOM;};

    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~CustomRichElementCustomNode(){CC_SAFE_RELEASE(_customNode);};

    
    /**
     * @brief Initialize a RichElementCustomNode with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param customNode A custom node pointer.
     * @return True if initialize success, false otherwise.
     */
    bool init(int tag, const cocos2d::Color3B& color, GLubyte opacity, cocos2d::Node* customNode);
    
    /**
     * @brief Create a RichElementCustomNode with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param customNode A custom node pointer.
     * @return A RichElementCustomNode instance.
     */
    static CustomRichElementCustomNode* create(int tag, const cocos2d::Color3B& color, GLubyte opacity, cocos2d::Node* customNode);
protected:
    cocos2d::Node* _customNode;
    friend class CustomRichText;
};
    
/**
 *@brief A container for displaying various RichElements.
 * We could use it to display texts with images easily.
 */
class CustomRichText : public cocos2d::ui::Widget, public CustomUIData, public CustomUIInterface
{
public:
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     */
    CustomRichText();
    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~CustomRichText();
    
    /**
     * @brief Create a empty RichText.
     *
     * @return RichText instance.
     */
    static CustomRichText* create();
    
    virtual void attach_node(cocos2d::Node* node);
    
    /**
     * @brief Insert a RichElement at a given index.
     *
     * @param element A RichElement type.
     * @param index A given index.
     */
    void insertElement(CustomRichElement* element, int index);
    
    /**
     * @brief Add a RichElement at the end of RichText.
     *
     * @param element A RichElement instance.
     */
    void pushBackElement(CustomRichElement* element);
    
    /**
     * @brief Remove a RichElement at a given index.
     *
     * @param index A integer index value.
     */
    void removeElement(int index);
    
    /**
     * @brief Remove specific RichElement.
     *
     * @param element A RichElement type.
     */
    void removeElement(CustomRichElement* element);
    
    /**
     * @brief Set vertical space between each RichElement.
     *
     * @param space Point in float.
     */
    void setVerticalSpace(float space);
    
    float getLastUpdateWidth() { return _last_update_width; }
    
    /**
     * @brief Rearrange all RichElement in the RichText.
     * It's usually called internally.
     */
    void formatText();
    void updateText(const bool force = false);
    
    void setOnLine(bool flag)
    {
        _one_line = flag;
    }

    //override functions.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;
    
    template <typename T>
    inline T getRichElement(int index) const { return static_cast<T>(_richElements.at(index)); }
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void adaptRenderers() override;

    virtual void initRenderer() override;
    void pushToContainer(cocos2d::Node* renderer);
    void handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const cocos2d::Color3B& color, GLubyte opacity);
    void handleImageRenderer(const std::string& fileParh, const cocos2d::Color3B& color, GLubyte opacity);
    void handleCustomRenderer(cocos2d::Node* renderer);
    void formarRenderers();
    void addNewLine();
protected:
    bool _formatTextDirty;
    cocos2d::Vector<CustomRichElement*> _richElements;
    std::vector<cocos2d::Vector<Node*>*> _elementRenders;
    float _leftSpaceWidth;
    float _verticalSpace;
    float _last_update_width;
    bool _one_line;
};

#endif /* defined(__CUSTOM_UIRichText__) */
