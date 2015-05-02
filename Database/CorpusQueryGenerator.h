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

public:
    /// Empty constructor
    QueryGenerator()
    {
    }

    /**
     * @brief getQueryOf
     * @param sentence : with syntax
     *
     * @note : Ambiguity of sentence type should be taken care of before using
     * 		   This functions
     * @return
     */
    string getQueryOf(const SyntaxTree& sentence)
    {
        /// First, determine what kind of sentence a tree has
        switch (sentence.getSentenceType ()) {
        case SentenceType::ST_INVALID:
            throw unimplemented_exc();
            break;
        case SentenceType::DECLARATIVE:
            return getInsertionQuery (sentence.getAll ());
            break;
        case SentenceType::INTERROGATIVE:
            throw unimplemented_exc();
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
    string getInsertionQuery(vector<SyntaxWord>& WordList)
    {
        // NOTE: DEBUG first
        cout << "Debug getInertionQuery\n";
        for(SyntaxWord w : WordList)
        {
            cout << w << endl;
        }
    }

}; /* -----  end of class QueryGenerator  ----- */


#endif /* !CORPUSQUERYGENERATOR_H */
