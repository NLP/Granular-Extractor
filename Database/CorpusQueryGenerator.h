/**
 * CorpusQueryGenerator.h
 * Copyright (C) 2015 Tony Lim <atomictheorist@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CORPUSQUERYGENERATOR_H
#define CORPUSQUERYGENERATOR_H
#include "../../Grammatica/Grammar Structure/Grammar-with-Map/cfgzero.h"
#include "../../Grammatica/Syntax-Tree/parser.h"
#include "../../Grammatica/Syntax-Tree/syntaxtree.h"
#include "../../CONFIG/config.h"
#include "../../CONFIG/nlp_exception.h"

using namespace NLP;

/**
 * @brief The QueryGenerator class
 * @note Require "SyntaxTree"
 *
 *  Class will convert the given SyntaxTree to a valid SQLite
 *  statements and pass it to OntologyDatabase for further process
 *
 *  To generate valid SQLite, the class will determine whether a SyntaxTree
 *  has DECLARATIVE , or INTERROGATIVE form of sentence.
 */
class QueryGenerator
{
    string mInsertHeader;

public:
    /// Empty constructor
    QueryGenerator()
    {
        mInsertHeader = "INSERT INTO ontology ";
    }

    string getQueryOf		(const SyntaxTree& sentence);	/// see implementation for comment
    string getInsertionQuery(const vector<SyntaxWord> &WordList);
    string getQuestionQuery (const vector<SyntaxWord> &WordList, const SyntaxObject& SObjBeingAsked);
}; /* -----  end of class QueryGenerator  ----- */

/********************************************
 *  Class Implementation Of QueryGenerator  *
 ********************************************/
/**
* @brief getQueryOf
* @param sentence : with syntax
* @note : Ambiguity of sentence type should be taken care of before using
* 		   This functions
* @return
*/
string QueryGenerator::getQueryOf(const SyntaxTree &sentence)
{
        /// First, determine what kind of sentence a tree has
        switch (sentence.getSentenceType ()) {
        case SentenceType::ST_INVALID:
            throw invalid_sentence();
            break;
        case SentenceType::DECLARATIVE:
            return getInsertionQuery(sentence.getAll());
            break;
        case SentenceType::INTERROGATIVE:
            return getQuestionQuery (sentence.getAll (), sentence.askingFor ());
            break;
        case SentenceType::IMPERATIVE:
            throw unimplemented_exc();
            break;
        default:
            break;
        }
}

/**
* @brief getInsertionQuery
* @param WordList
*
*  @note here's where conversion to sql language takes place
* @return string of SQLite command
*/
string QueryGenerator::getInsertionQuery(const vector<SyntaxWord>& WordList)
{
    set<SyntaxObject> SPO; // SPO components to put on table
    string columnToFill;
    string  valueToFill;

    for(SyntaxWord const& w : WordList)
    {
        switch (w.getSyntax ()) {
        case SyntaxObject::SUBJECT:
        case SyntaxObject::MAINVERB:
        case SyntaxObject::INDIRECTOBJ:
        case SyntaxObject::DIRECTOBJ:
//        case SyntaxObject::ATTRIBUTE:  // Should be adjective
            columnToFill += syntaxDBLookUp[w.getSyntax ()];
            columnToFill += ",";
            valueToFill += "'";
            valueToFill += w.getWord ().getName ();
            valueToFill += "',";
            break;
        default:
            break;
        }
    }
    columnToFill = columnToFill.substr (0, columnToFill.size () - 1);
    valueToFill = valueToFill.	substr (0, valueToFill.size () - 1);
    string result = mInsertHeader + "(" + columnToFill + ")" + " VALUES ("
            + valueToFill + ");";
    return result;
}

/**
 * @brief QueryGenerator::getQuestionQuery
 * 		From a structure of wordlist, generate valid query.
 * @param WordList
 * @return
 */
string QueryGenerator::getQuestionQuery(const vector<SyntaxWord> &WordList, const SyntaxObject &SObjBeingAsked)
{
//    cout << "--DEBUG" << endl;
//    cout << "syntax encoding : " << SyntaxTree::getSyntaxEncoding (WordList) << endl;
//    cout << "Being asked : " << syntaxStrEncoding[SObjBeingAsked] << endl;

    /// depending on what being asked, produce a query
    string query = "SELECT " + syntaxDBLookUp[SObjBeingAsked] + " FROM ontology WHERE ";
    for(SyntaxWord const& sw : WordList) {
        if(sw.getSyntax () != SObjBeingAsked && sw.getSyntax () != S_INVALID) {
            query += syntaxDBLookUp[sw.getSyntax()] + " LIKE ";
            query += ("'" + sw.getWord ().getTokenString () + "%'");
            query += " AND ";
        }
    }
    query = query.substr (0, query.size () - 5);		/// Chop the last " AND "
//    cout << " DEBUG : query : " << query << endl;
    return query;
}



#endif /* !CORPUSQUERYGENERATOR_H */
