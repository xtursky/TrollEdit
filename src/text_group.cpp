/**
 * @Title text_group.cpp
 * ---------------------------------------------------------------------------
 * @Description Contains the defintion of class TextGroup.
 * @Author Team 04 Ufopak + Team 10 Innovators
 */

#include "text_group.h"

#include "document_scene.h"
#include "block_group.h"

#include "tree_element.h"
#include "block.h"
#include "text_item.h"
#include <QTextItem>

TextGroup::TextGroup(BlockGroup *block, DocumentScene *scene)
    : QGraphicsTextItem(0, scene)
{
    this->block = block;
    this->scene = scene;

//    this->setPlainText(block->toText());
    this->setPos(block->pos().x(),block->pos().y());
    this->setScale(block->scale());
    this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);
    this->setTextInteractionFlags(Qt::TextEditorInteraction);

    Block *temp = new Block(new TreeElement("temp"), 0, block);
    QFont *f = new QFont(temp->textItem()->font());
    this->setFont(*f);
}

TextGroup::~TextGroup()
{

}

void TextGroup::changeMode(){
}

void TextGroup::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        if ((event->modifiers() & Qt::AltModifier) == Qt::AltModifier)
        {
            block->changeMode();
            event->accept();
        }
        else
        {
//            QGraphicsTextItem::mousePressEvent(event);
        }
    }
    QGraphicsTextItem::mousePressEvent(event);
}
