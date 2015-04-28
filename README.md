Granular Extractor
=====================================================

Task:
1.  RDF (Resource Development Framework) from extracted entities
    Given : (subject - predicate - object - LOC - TIME)
    Fill SQLite database with corresponding entities

2. Query request commands
    Define a set of known question patterns that can be translated to query language.
    Example : 
        - Who eats apple ?              :   select subject from table where predicate = 'Eat' AND object = 'Apple'
        - Where does he he eats apple ? :   select LOC from table where predicate = 'Eat' AND object = 'Apple' AND subject = 'He'
        - etcs

3. Query result language
    The result of queried request is converted to English language.


