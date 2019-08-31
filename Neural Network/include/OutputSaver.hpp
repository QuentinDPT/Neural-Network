#ifndef OUTPUTSAVER_HPP
#define OUTPUTSAVER_HPP

#include <vector>
#include <string>

namespace OutputSaver{
    class OutputElement{
        public :
            OutputElement(std::string name, std::string data) : m_title(name), m_data(data) {}

            virtual void exportMarkdown() ;

        private :
            std::string m_title ;
            std::string m_data ;
    } ;

    class Info : OutputElement{
        public :
            Info(std::string name, std::string data) : OutputElement(name,data) {}

            void exportMarkdown() ;
    } ;

    class Error : OutputElement{
        public :
            Error(std::string name, std::string data) : OutputElement(name,data) {}

            void exportMarkdown() ;
    } ;

    class Output{
        public :
            Output(bool visible) ;

            void exportMarkdown() ;

        private :
            std::vector<OutputElement> m_logs ;
            bool m_visible ;
    } ;
} ;

#endif // OUTPUTSAVER_HPP
