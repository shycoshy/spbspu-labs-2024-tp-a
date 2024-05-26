#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iosfwd>
#include <map>
#include <set>
#include <string>

namespace demidenko
{
  class Dictionary
  {
  public:
    using Record = std::pair< std::string, std::set< std::string > >;
    Dictionary();
    bool addRecord(Record&& record);
    bool removeRecord(const Record& record);
    void translate(const std::string& word, std::ostream& out) const;
    void search(const std::string& translation, std::ostream& out) const;
    void prefix(const std::string& prefix, std::ostream& out) const;
    void merge(const Dictionary& other);
    void exclude(const Dictionary& other);
    void split(const std::string& word, Dictionary& first, Dictionary& second);

    friend std::istream& operator>>(std::istream& in, Dictionary& dictionary);
    friend std::ostream& operator<<(std::ostream& out, Dictionary& dictionary);

  private:
    std::map< std::string, std::set< std::string > > tree_;
  };
  std::istream& operator>>(std::istream& in, Dictionary& dictionary);
  std::ostream& operator<<(std::ostream& out, Dictionary& dictionary);
}

#endif
