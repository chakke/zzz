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

#include "CustomUIRichText.h"
#include "platform/CCFileUtils.h"
#include "2d/CCLabel.h"
#include "2d/CCSprite.h"
#include "base/ccUTF8.h"
#include "ui/UIHelper.h"

USING_NS_CC;

class CustomUIRichTextLabel : public cocos2d::Label
{
public:
    
    CustomUIRichTextLabel(TextHAlignment hAlignment, TextVAlignment vAlignment) : Label(hAlignment, vAlignment)
    {
    }
    
    static CustomUIRichTextLabel* createWithTTF(const std::string& text, const std::string& fontFile, float fontSize, const Size& dimensions = Size::ZERO , TextHAlignment hAlignment = TextHAlignment::LEFT, TextVAlignment vAlignment = TextVAlignment::TOP)
    {
        auto ret = new (std::nothrow) CustomUIRichTextLabel(hAlignment,vAlignment);
        
        if (ret && FileUtils::getInstance()->isFileExist(fontFile))
        {
            TTFConfig ttfConfig(fontFile.c_str(),fontSize,GlyphCollection::DYNAMIC);
            if (ret->setTTFConfig(ttfConfig))
            {
                ret->setDimensions(dimensions.width,dimensions.height);
                ret->setString(text);
                
                ret->autorelease();
                
                return ret;
            }
        }
        
        delete ret;
        return nullptr;
    }
    
//    void onDraw(const Mat4& transform, bool transformUpdated)
//    {
////        GL::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        auto glprogram = getGLProgram();
//        glprogram->use();
//        glprogram->setUniformsForBuiltins(transform);
//        glprogram->setUniformLocationWith4f(_uniformTextColor,
//                                            _textColorF.r, _textColorF.g, _textColorF.b, _textColorF.a);
//        for (auto&& batchNode : _batchNodes)
//        {
//            batchNode->getTextureAtlas()->drawQuads();
//        }
//    }
//    
//    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
//    {
//        if (_batchNodes.empty() || _lengthOfString <= 0)
//        {
//            return;
//        }
//        // Don't do calculate the culling if the transform was not updated
//        bool transformUpdated = flags & FLAGS_TRANSFORM_DIRTY;
//#if CC_USE_CULLING
//        auto visitingCamera = Camera::getVisitingCamera();
//        auto defaultCamera = Camera::getDefaultCamera();
//        if (visitingCamera == defaultCamera) {
//            _insideBounds = (transformUpdated || visitingCamera->isViewProjectionUpdated()) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
//        }
//        else
//        {
//            _insideBounds = renderer->checkVisibility(transform, _contentSize);
//        }
//        
//        if (_insideBounds)
//#endif
//        {
//            _customCommand.init(_globalZOrder, transform, flags);
//            _customCommand.func = CC_CALLBACK_0(CustomUIRichTextLabel::onDraw, this, transform, transformUpdated);
//            
//            renderer->addCommand(&_customCommand);
//        }
//    }
//    
//    virtual void updateShaderProgram()
//    {
//        setShader("res/shaders/text.vsh", "res/shaders/text.fsh");
//        _uniformTextColor = glGetUniformLocation(getGLProgram()->getProgram(), "u_textColor");
//    }
//
//    void setShader(const std::string& vertfile, const std::string& fragfile)
//    {
//        std::string vsh = vertfile;
//        std::string fsh = fragfile;
//        auto glprogram = GLProgramCache::getInstance()->getGLProgram(vsh+fsh);
//        if (!glprogram)
//        {
//            glprogram = GLProgram::createWithFilenames(vsh, fsh);
//            GLProgramCache::getInstance()->addGLProgram(glprogram, vsh+fsh);
//        }
//        
//        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
//        setGLProgramState(glprogramstate);
//    }
};

bool CustomRichElement::init(int tag, const Color3B &color, GLubyte opacity)
{
    _tag = tag;
    _color = color;
    _opacity = opacity;
    return true;
}
    
    
CustomRichElementText* CustomRichElementText::create(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize)
{
    CustomRichElementText* element = new (std::nothrow) CustomRichElementText();
    if (element && element->init(tag, color, opacity, text, fontName, fontSize))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool CustomRichElementText::init(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize)
{
    if (CustomRichElement::init(tag, color, opacity))
    {
        _text = text;
        _fontName = fontName;
        _fontSize = fontSize;
        return true;
    }
    return false;
}

CustomRichElementImage* CustomRichElementImage::create(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
{
    CustomRichElementImage* element = new (std::nothrow) CustomRichElementImage();
    if (element && element->init(tag, color, opacity, filePath))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool CustomRichElementImage::init(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
{
    if (CustomRichElement::init(tag, color, opacity))
    {
        _filePath = filePath;
        return true;
    }
    return false;
}

CustomRichElementCustomNode* CustomRichElementCustomNode::create(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
{
    CustomRichElementCustomNode* element = new (std::nothrow) CustomRichElementCustomNode();
    if (element && element->init(tag, color, opacity, customNode))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool CustomRichElementCustomNode::init(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
{
    if (CustomRichElement::init(tag, color, opacity))
    {
        _customNode = customNode;
        _customNode->retain();
        return true;
    }
    return false;
}
    
CustomRichText::CustomRichText():
_formatTextDirty(true),
_leftSpaceWidth(0.0f),
_verticalSpace(0.0f),
_last_update_width(0),
_one_line(false)
{
}
    
CustomRichText::~CustomRichText()
{
    _richElements.clear();
}
    
CustomRichText* CustomRichText::create()
{
    CustomRichText* widget = new (std::nothrow) CustomRichText();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
bool CustomRichText::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}
    
void CustomRichText::initRenderer()
{
}

void CustomRichText::insertElement(CustomRichElement *element, int index)
{
    _richElements.insert(index, element);
    _formatTextDirty = true;
}
    
void CustomRichText::pushBackElement(CustomRichElement *element)
{
    _richElements.pushBack(element);
    _formatTextDirty = true;
}
    
void CustomRichText::removeElement(int index)
{
    _richElements.erase(index);
    _formatTextDirty = true;
}
    
void CustomRichText::removeElement(CustomRichElement *element)
{
    _richElements.eraseObject(element);
    _formatTextDirty = true;
}

void CustomRichText::updateText(bool force)
{
    if (_last_update_width != _contentSize.width || force)
    {
        _last_update_width = _contentSize.width;
        _formatTextDirty = true;
        _customSize.height = 0;
        formatText();
    }
}
    
void CustomRichText::formatText()
{
    if (_formatTextDirty)
    {
        this->removeAllProtectedChildren();
        _elementRenders.clear();
        if (_ignoreSize)
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                CustomRichElement* element = _richElements.at(i);
                Node* elementRenderer = nullptr;
                switch (element->_type)
                {
                    case CustomRichElement::Type::TEXT:
                    {
                        CustomRichElementText* elmtText = static_cast<CustomRichElementText*>(element);
                        if (FileUtils::getInstance()->isFileExist(elmtText->_fontName))
                        {
                            elementRenderer = CustomUIRichTextLabel::createWithTTF(elmtText->_text.c_str(), elmtText->_fontName, elmtText->_fontSize);
                        }
                        else
                        {
                            elementRenderer = CustomUIRichTextLabel::createWithSystemFont(elmtText->_text.c_str(), elmtText->_fontName, elmtText->_fontSize);
                        }
                        break;
                    }
                    case CustomRichElement::Type::IMAGE:
                    {
                        CustomRichElementImage* elmtImage = static_cast<CustomRichElementImage*>(element);
                        elementRenderer = Sprite::create(elmtImage->_filePath.c_str());
                        break;
                    }
                    case CustomRichElement::Type::CUSTOM:
                    {
                        CustomRichElementCustomNode* elmtCustom = static_cast<CustomRichElementCustomNode*>(element);
                        elementRenderer = elmtCustom->_customNode;
                        break;
                    }
                    default:
                        break;
                }
                elementRenderer->setColor(element->_color);
                elementRenderer->setOpacity(element->_opacity);
                pushToContainer(elementRenderer);
            }
        }
        else
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                
                CustomRichElement* element = static_cast<CustomRichElement*>(_richElements.at(i));
                switch (element->_type)
                {
                    case CustomRichElement::Type::TEXT:
                    {
                        CustomRichElementText* elmtText = static_cast<CustomRichElementText*>(element);
                        handleTextRenderer(elmtText->_text.c_str(), elmtText->_fontName.c_str(), elmtText->_fontSize, elmtText->_color, elmtText->_opacity);
                        break;
                    }
                    case CustomRichElement::Type::IMAGE:
                    {
                        CustomRichElementImage* elmtImage = static_cast<CustomRichElementImage*>(element);
                        handleImageRenderer(elmtImage->_filePath.c_str(), elmtImage->_color, elmtImage->_opacity);
                        break;
                    }
                    case CustomRichElement::Type::CUSTOM:
                    {
                        CustomRichElementCustomNode* elmtCustom = static_cast<CustomRichElementCustomNode*>(element);
                        handleCustomRenderer(elmtCustom->_customNode);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        formarRenderers();
        _formatTextDirty = false;
    }
}
    
void CustomRichText::handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B &color, GLubyte opacity)
{
    auto fileExist = FileUtils::getInstance()->isFileExist(fontName);
    Label* textRenderer = nullptr;
    if (fileExist)
    {
        textRenderer = CustomUIRichTextLabel::createWithTTF(text, fontName, fontSize);
    } 
    else
    {
        textRenderer = CustomUIRichTextLabel::createWithSystemFont(text, fontName, fontSize);
    }
    if (_one_line)
    {
        textRenderer->setColor(color);
        textRenderer->setOpacity(opacity);
        pushToContainer(textRenderer);
    }
    else
    {
        float textRendererWidth = textRenderer->getContentSize().width;
        _leftSpaceWidth -= textRendererWidth;
        if (_leftSpaceWidth < 0.0f)
        {
            float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
            std::string curText = text;
            size_t stringLength = StringUtils::getCharacterCountInUTF8String(text);
            int leftLength = stringLength * (1.0f - overstepPercent);
            //The minimum cut length is 1, otherwise will cause the infinite loop.
            if (0 == leftLength) leftLength = 1;
            std::string leftWords = ui::Helper::getSubStringOfUTF8String(curText,0,leftLength);
            std::string cutWords = ui::Helper::getSubStringOfUTF8String(curText, leftLength, stringLength - leftLength);
            if (leftLength > 0)
            {
                Label* leftRenderer = nullptr;
                if (fileExist)
                {
                    leftRenderer = CustomUIRichTextLabel::createWithTTF(ui::Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), fontName, fontSize);
                }
                else
                {
                    leftRenderer = CustomUIRichTextLabel::createWithSystemFont(ui::Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), fontName, fontSize);
                }
                if (leftRenderer)
                {
                    if (_customSize.width > 0)
                    {
                        while (leftRenderer->getContentSize().width > _customSize.width || (leftWords.length() > 0 && ! StringUtils::isUnicodeSpace(leftWords.at(leftWords.length()-1)))) {
                            leftLength--;
                            leftWords = ui::Helper::getSubStringOfUTF8String(curText,0,leftLength);
                            leftRenderer->setString(leftWords);
                        }
                        cutWords = ui::Helper::getSubStringOfUTF8String(curText, leftLength, stringLength - leftLength);
                    }
                    leftRenderer->setColor(color);
                    leftRenderer->setOpacity(opacity);
                    pushToContainer(leftRenderer);
                }
            }
            if (leftLength > 0)
            {
                addNewLine();
                handleTextRenderer(cutWords.c_str(), fontName, fontSize, color, opacity);
            }
        }
        else
        {
            textRenderer->setColor(color);
            textRenderer->setOpacity(opacity);
            pushToContainer(textRenderer);
        }
    }
}
    
void CustomRichText::handleImageRenderer(const std::string& fileParh, const Color3B &color, GLubyte opacity)
{
    Sprite* imageRenderer = Sprite::create(fileParh);
    handleCustomRenderer(imageRenderer);
}
    
void CustomRichText::handleCustomRenderer(cocos2d::Node *renderer)
{
    Size imgSize = renderer->getContentSize();
    _leftSpaceWidth -= imgSize.width;
    if (_leftSpaceWidth < 0.0f)
    {
        addNewLine();
        pushToContainer(renderer);
        _leftSpaceWidth -= imgSize.width;
    }
    else
    {
        pushToContainer(renderer);
    }
}
    
void CustomRichText::addNewLine()
{
    _leftSpaceWidth = _customSize.width;
    _elementRenders.push_back(new Vector<Node*>());
}

void CustomRichText::formarRenderers()
{
    if (_ignoreSize)
    {
        float newContentSizeWidth = 0.0f;
        float newContentSizeHeight = 0.0f;
        
        Vector<Node*>* row = (_elementRenders[0]);
        float nextPosX = 0.0f;
        for (ssize_t j=0; j<row->size(); j++)
        {
            Node* l = row->at(j);
            l->setAnchorPoint(Vec2::ZERO);
            l->setPosition(nextPosX, 0.0f);
            this->addProtectedChild(l, 1);
            Size iSize = l->getContentSize();
            newContentSizeWidth += iSize.width;
            newContentSizeHeight = MAX(newContentSizeHeight, iSize.height);
            nextPosX += iSize.width;
        }
        this->setContentSize(Size(newContentSizeWidth, newContentSizeHeight));
    }
    else
    {
        float newContentSizeHeight = 0.0f;
        float max_width = 0.0;
        float *maxHeights = new float[_elementRenders.size()];
        
        for (size_t i=0; i<_elementRenders.size(); i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float maxHeight = 0.0f;
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                maxHeight = MAX(l->getContentSize().height, maxHeight);
            }
            maxHeights[i] = maxHeight;
            newContentSizeHeight += maxHeights[i];
        }
        
        float nextPosY = _customSize.height;
        for (size_t i=0; i<_elementRenders.size(); i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float nextPosX = 0.0f;
            nextPosY -= (maxHeights[i] + _verticalSpace);
            
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                l->setAnchorPoint(Vec2::ZERO);
                l->setPosition(nextPosX, nextPosY + newContentSizeHeight);
                this->addProtectedChild(l, 1);
                nextPosX += l->getContentSize().width;
            }
            max_width = MAX(max_width, nextPosX);
        }
        delete [] maxHeights;
        _customSize.height = newContentSizeHeight;
        _customSize.width = max_width;
    }
    
    size_t length = _elementRenders.size();
    for (size_t i = 0; i<length; i++)
	{
        Vector<Node*>* l = _elementRenders[i];
        l->clear();
        delete l;
	}    
    _elementRenders.clear();
    
    if (_ignoreSize)
    {
        Size s = getVirtualRendererSize();
        this->setContentSize(s);
    }
    else
    {
        this->setContentSize(_customSize);
    }
    updateContentSizeWithTextureSize(_contentSize);
}
    
void CustomRichText::adaptRenderers()
{
    this->formatText();
}

void CustomRichText::pushToContainer(cocos2d::Node *renderer)
{
    if (_elementRenders.size() <= 0)
    {
        return;
    }
    _elementRenders[_elementRenders.size()-1]->pushBack(renderer);
}
    
void CustomRichText::setVerticalSpace(float space)
{
    _verticalSpace = space;
}

void CustomRichText::ignoreContentAdaptWithSize(bool ignore)
{
    if (_ignoreSize != ignore)
    {
        _formatTextDirty = true;
        Widget::ignoreContentAdaptWithSize(ignore);
    }
}
    
std::string CustomRichText::getDescription() const
{
    return "CustomRichText";
}

void CustomRichText::attach_node(cocos2d::Node* node)
{
    addChild(node);
}