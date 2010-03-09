#ifndef TREEELEMENT_H
#define TREEELEMENT_H

#include <QList>
#include <QString>

class TreeElement
{
public:
     TreeElement(QString type);
     ~TreeElement();

     void setType(QString type);
     void appendChild(TreeElement *child);
     void appendChildren(QList<TreeElement *> children);
     void insertChild(int index, TreeElement *child);
     void insertChildren(int index, QList<TreeElement *> children);
     void removeChild(TreeElement *child);
     void removeAllChildren();
     int childCount();
     int indexOfChild(TreeElement* child);
     bool isLeaf();
     bool hasSiblings();

     TreeElement *operator<<(TreeElement *child);
     TreeElement *operator<<(QList<TreeElement *> children);
     TreeElement *operator[](int index);
     int operator[](TreeElement* child);

     QList<TreeElement *> getChildren();
     QList<TreeElement *> getAncestors();
     QList<TreeElement *> getDescendants();
     TreeElement *getRoot();
     TreeElement *getParent();
     QString getType();
     QString getText();

     bool hasNext();
     TreeElement *next();

 protected:
     TreeElement *parent;

 private:
     QList<TreeElement *> children;
     QString type;
     bool hasNext(int index);
     TreeElement *next(int index);
};

#endif // TREEELEMENT_H