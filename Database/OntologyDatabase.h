/**
 * OntologyDatabase.h
 * Copyright (C) 2015 Tony Lim <atomictheorist@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ONTOLOGYDATABASE_H
#define ONTOLOGYDATABASE_H

#include <string>
#include <list>
#include <QtSql>

using namespace std;


const QString DBPATH_ONT = "../../Granular-Extractor/ont_db.sqlite";

/**
 * @brief The OntologyDatabase class
 * 		The class acts as the interface that allows communication with database.
 * 		class will be used by higher process that handles the sqlite query generation
 * 		from a structure of SyntaxTree
 */
class OntologyDatabase
{
private:
    static QSqlDatabase mOntDB;
    vector<string> vectorQuestionQuery(const string &qrStr);   /// lower function

public:
    OntologyDatabase();
    void InsertionQuery(const string &qrStr);
    void QuestionQuery (const string &qrStr, string& result);  /// Upper function

    ~OntologyDatabase();
}; /* -----  end of class OntologyDatabase  ----- */

/// static declaration and initialization of database
QSqlDatabase OntologyDatabase::mOntDB = QSqlDatabase::addDatabase("QSQLITE", "ONT_DB");

/**
 * @brief OntologyDatabase::OntologyDatabase
 * constructor to open connections to database
 */
OntologyDatabase::OntologyDatabase()
{
    mOntDB.setDatabaseName (DBPATH_ONT);
        if( !mOntDB.open() ) {
            qDebug() << mOntDB.lastError();
            qFatal( "Failed to connect to database." );
            throw std::invalid_argument("Error: Invalid database");
        } else { qDebug() << "Debug: Database opened." << endl; }
}

/**
 * @brief OntologyDatabase::InsertionQuery
 * 		Given a string that is a valid SQLite form
 * 		The function will proceed with insertion to database
 * @param qrStr
 */
void OntologyDatabase::InsertionQuery(const string& qrStr)
{
    QSqlQuery    mLiteQr(this->mOntDB);
    mLiteQr.prepare(qrStr.c_str());
    if( !mLiteQr.exec() ) {
        qDebug() << mLiteQr.lastError();
        throw std::invalid_argument("Invalid query.");
    }
}

/**
 * @brief QuestionQuery
 *
 * @param qrStr		: query commands
 * @param result    : reply
 */
void OntologyDatabase::QuestionQuery(const string &qrStr, string& result)  /// Upper function
{
    vector<string> v_result = vectorQuestionQuery (qrStr);
    result = "";
    for(string R : v_result)
      result += (R + ",");
    /// TODO : Make result neater
}


/**
 * @brief ValueQuestionQuery
 * 	Given a string of valid SQLite query, the function will
 *  populate a vector with a result from the query
 *
 * @param qrStr
 * @return
 */
vector<string> OntologyDatabase::vectorQuestionQuery(const string &qrStr)
{
    QSqlQuery	mLiteQr(this->mOntDB);
    mLiteQr.prepare (qrStr.c_str ());
    if( !mLiteQr.exec() ) {
        qDebug() << mLiteQr.lastError();
        throw std::invalid_argument("Invalid query.");
    }

    vector<string> resultList;
    /// Extracting process
    while( mLiteQr.next() ) {
         resultList.push_back (mLiteQr.value(0).toString().toStdString());
    }
}

/// Destructor
OntologyDatabase::~OntologyDatabase()
{
}


#endif /* !ONTOLOGYDATABASE_H */
