/*
 * @copyright &copy; 2014 by Hammond Street Developments Pty Ltd.
 *  All Rights Reserved
 * @file test_json.cpp
 *
 * @author Denis Dowling (Denis.Dowling@hsd.com.au)
 *
 * Description : Test the JSON classes
 */
#include "JSON.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace JSON;

const char *ex1 =
"{"
"    \"glossary\": {"
"        \"title\": \"example glossary\","
"	    \"GlossDiv\": {"
"            \"title\": \"S\","
"		\"GlossList\": {"
"                \"GlossEntry\": {"
"                    \"ID\": \"SGML\","
"			\"SortAs\": \"SGML\","
"			\"GlossTerm\": \"Standard Generalized Markup Language\","
"			\"Acronym\": \"SGML\","
"			\"Abbrev\": \"ISO 8879:1986\","
"			\"GlossDef\": {"
"                        \"para\": \"A meta-markup language, used to create markup languages such as DocBook.\","
"			    \"GlossSeeAlso\": [\"GML\", \"XML\"]"
"			    },"
"			\"GlossSee\": \"markup\""
"			    }"
"            }"
"        }"
"    }"
"}";

int main(int argc, char **argv)
{
    if (argc > 1)
    {
	const char *file = argv[1];

        ifstream t(file);
        string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

	Parser parser(
	ALLOW_COMMENTS /* |
	ALLOW_UNQUOTED_FIELD_NAMES |
	ALLOW_SINGLE_QUOTES |
	ALLOW_TRAILING_COMMAS */
	);

	ValuePtr v = parser.parse(str);

	cout << file << " Parsed to JSON objects : " << endl;
	cout << v->encodePretty() << endl;

	return 0;
    }

    ObjectPtr window(new Object);
    window->setProperty("title", "Sample Widget");
    window->setProperty("name", "main_window");
    window->setProperty("width", 500);
    window->setProperty("height", 400);
    window->setProperty("open", true);
    window->setProperty("text",
			"This is some long text\r\n"
			"This is the next line\r\n"
			"Some control characters \x01\t\b\f\xff");

    ObjectPtr image(new Object);
    image->setProperty("src", "Images/logo.png");
    image->setProperty("name", "logo");
    image->setProperty("hOffset", 250);
    image->setProperty("vOffset", 100);

    ObjectPtr widget(new Object);
    widget->setProperty("debug", true);
    widget->setProperty("window", window);
    widget->setProperty("image", image);

    ArrayPtr path(new Array);
    for (int i = 0; i < 20; i++)
    {
	ArrayPtr point(new Array);
	point->add(i);
	point->add(i);
	point->add("point");

	path->add(point);
    }
    widget->setProperty("path", path);

    cout << "JSON:" << endl;
    cout << widget->encode() << endl;

    cout << "Pretty JSON:" << endl;
    cout << widget->encodePretty() << endl;

    Parser parser(
	ALLOW_COMMENTS |
	ALLOW_UNQUOTED_FIELD_NAMES |
	ALLOW_SINGLE_QUOTES |
	ALLOW_TRAILING_COMMAS
	);

    ValuePtr v = parser.parse(ex1);

    cout << "Pretty JSON:" << endl;
    cout << v->encodePretty() << endl;

    assert(v->isObject());
    ObjectPtr obj = boost::dynamic_pointer_cast<JSON::Object>(v);

    ValuePtr v2 = obj->properties["glossary"];
    assert(v2);
    assert(v2->isObject());
    ObjectPtr obj2 = boost::dynamic_pointer_cast<JSON::Object>(v2);
    std::string title;
    obj2->getProperty("title", title);
    cout << "Found title : " << title << endl;
    assert(title == "example glossary");

    const char *examples[] = {
	"test_json1.json",
	"test_json2.json",
	"test_json3.json",
	"test_json4.json",
	"test_json5.json",
	"test_json6.json",
	"test_json7.json",
	"test_json8.json",
	"test_json9.json",
	"test_json10.json",
	"test_json11.json",
	"test_json12.json",
	"test_json13.json",
	"test_json14.json",
	"test_json15.json",
    };

    for (const char **ex = examples;
	 ex != examples + sizeof(examples)/sizeof(char *);
	 ex++)
    {
        string file = string(TEST_DATA_DIR) + string("/") + string(*ex);
        cout << "Reading file " << file << endl;

        ifstream t(file.c_str());
        string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

        cout << "Parsing JSON" << endl;
	v = parser.parse(str);

	cout << *ex << " parsed to JSON:" << endl;
	cout << v->encodePretty() << endl;
    }

    cout << endl << "All done!!" << endl;

    return 0;
}
