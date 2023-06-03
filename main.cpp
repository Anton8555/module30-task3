#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cpr/cpr.h>

// combining query identifier constants
enum HTML_queries{ htmlNone, htmlPost, htmlGet };

/*!
 * @brief The function identifies the request by line.
 * @param inStr a string for identification.
 * @return Returns the constant identifier of the request type.
*/
HTML_queries identification(const std::string &inStr)
{
    if( inStr == "post" )
        return htmlPost;
    else
    if( inStr == "get" )
        return htmlGet;

    return htmlNone;
}

/*!
 * @brief The Post-request run routine.
 * @param inArgument a list of arguments in a dictionary type structure.
 */
void runPost(std::map<std::string, std::string> inArguments) {
    // creating a cpr object::Payload
    std::vector<cpr::Pair> vec1;
    vec1.clear();
    for (std::map<std::string, std::string>::iterator it = inArguments.begin(); it != inArguments.end(); it++)
    {
        std::string
            key = it->first,
            value = it->second;
        vec1.push_back(cpr::Pair((std::string)key, (std::string)value));
    }
    cpr::Payload array1(vec1.begin(), vec1.end());

    // executing a query with arguments
    std::cout << "A request is being made. Wait..." << std::endl;
    cpr::Response r = cpr::Post(
        cpr::Url("http://httpbin.org/post"),
        cpr::Payload(array1)
    );

    // output of the result
    std::cout
        << "Answer:" << std::endl
        << r.text << std::endl;
}

/*!
 * @brief The Get-request run routine.
 * @param inArgument a list of arguments in a dictionary type structure.
 */
void runGet(std::map<std::string, std::string> inArguments) {
    // the address to which the request is made
    const std::string urlGet = "http://httpbin.org/get";
    
    // creating an argument string
    std::string argGet = "?";
    for (std::map<std::string, std::string>::iterator it = inArguments.begin(); it != inArguments.end(); it++, argGet+="&")
    {
        argGet += it->first + "=" + it->second;
    }

    // executing a query with arguments
    std::cout << "A request is being made. Wait..." << std::endl;
    cpr::Response r = cpr::Get(cpr::Url(urlGet + argGet));

    // output of the result
    std::cout
        << "Answer:" << std::endl
        << r.text << std::endl;
}

int main() {
    // data
    std::map<std::string, std::string> arguments;  // list of arguments
    HTML_queries id_queries;  // request identifier

    //-------------------------------------------------------------------------------------------------
    // entering arguments
    arguments.clear();
    while(true){
        std::string key,value;

        // entering the name of the argument or request
        std::cout << "Enter the name of the argument or the type of request: ";
        std::cin >> key;
        // name analysis
        if( (id_queries=identification(key)) != htmlNone )
            // if the name is defined as a query, then exit the argument input loop
            break;
        // entering a value
        std::cout << "Enter the value of the argument: ";
        std::cin >> value;

        // adding an argument to the dictionary
        arguments.insert(std::pair<std::string, std::string> (key, value));
    }

    //-------------------------------------------------------------------------------------------------
    // request execution
    switch (id_queries)
    {
    case htmlPost:
        runPost(arguments);
        break;

    case htmlGet:
        runGet(arguments);
        break;

    default:
        std::cout << "Error in the program.\n";
        break;
    }

    //-------------------------------------------------------------------------------------------------
    // program shutdown
    std::cout << "\nEnd of program." << std::endl;
    return 0;
}
