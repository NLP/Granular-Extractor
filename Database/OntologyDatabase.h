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

public:
    OntologyDatabase();

    /// TODO : make interface for insertion queries (EASY)
    void testInsertionQuery(const string &qrStr);

    /// TODO : make interface for request queries (HARD)

    ~OntologyDatabase();
}; /* -----  end of class OntologyDatabase  ----- */

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

/// testing InsertionQuery
void OntologyDatabase::testInsertionQuery(const string& qrStr)
{
    QSqlQuery    mLiteQr(this->mOntDB);
    mLiteQr.prepare (qrStr.c_str ());
    mLiteQr.prepare(qrStr.c_str());
    if( !mLiteQr.exec() ) {
        qDebug() << mLiteQr.lastError();
        throw std::invalid_argument("Invalid query.");
    }
}

/// Destructor
OntologyDatabase::~OntologyDatabase()
{
}


#endif /* !ONTOLOGYDATABASE_H */
