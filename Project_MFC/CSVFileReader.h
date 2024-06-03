#pragma once
#include <vector>
#include <string>

class CSVFileReader
{
public:
    CSVFileReader(const CString& filePath);
    bool ReadCSV();
    std::vector<std::vector<std::string>> GetData() const;

private:
    CString m_filePath;
    std::vector<std::vector<std::string>> m_data;
};
