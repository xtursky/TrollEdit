#ifndef ANALYZER_H
#define ANALYZER_H

#include <QMessageBox>
#include <QHash>
#include <QList>

class TreeElement;

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
int luaopen_lpeg (lua_State *L);
}

class Analyzer
{
public:
    Analyzer(QString script);
    ~Analyzer();
    TreeElement *analyzeFull(QString input);
    TreeElement *analyzeElement(TreeElement *element);
    TreeElement *getAnalysableAncestor(TreeElement *element);
    QStringList getExtensions() const {return extensions;}
    QString getLanguageName() const {return langName;}
    QString getSnippet() const {return defaultSnippet;}
    QList<QPair<QString, QHash<QString, QString> > > readConfig(QString fileName);
    void readSnippet(QString fileName);
    static const QString TAB;

private:
    static const char *EXTENSIONS_FIELD;
    static const char *LANGUAGE_FIELD;
    static const char *MAIN_GRAMMAR_FIELD;
    static const char *SUB_GRAMMARS_FIELD;
    static const char *PAIRED_TOKENS_FIELD;
    static const char *SELECTABLE_TOKENS_FIELD;
    static const char *MULTI_TEXT_TOKENS_FIELD;
    static const char *FLOATING_TOKENS_FIELD;
    static const char *CONFIG_KEYS_FIELD;

    lua_State *L;               // the Lua interpreter
    QStringList extensions;     // types of files to be analyzed
    QString langName;           // name/description of analyzed language(s)
    QString scriptName;        // script name
    QString mainGrammar;        // name of complete gramar
    QHash<QString, QString> subGrammars;// names of partial grammars
    QStringList pairedTokens;           // list of paired tokens, example: "{", "}", "begin", "end"...
    QStringList selectableTokens;       // list of tokens which can contain line-breaking children
    QStringList multiTextTokens;        // list of tokens which can contain more lines of text
    QStringList floatingTokens;         // list of tokens allowed to say out of hierarchy
    QString defaultSnippet;             // code that will be displayed in new file

    void setupConstants();
    TreeElement* analyzeString(QString grammar, QString input);
    TreeElement* createTreeFromLuaStack();
    void checkPairing(TreeElement *element);

    void processWhites(TreeElement *root); // move all whites as high as possible without changing tree text

    QMessageBox *msgBox; // for (error) mesasage
};

#endif // ANALYZER_H
