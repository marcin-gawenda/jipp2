#include "pch.h"
#include "CSVFileReader.h"
#include <sstream>
#include <afx.h>

CSVFileReader::CSVFileReader(const CString& filePath)
    : m_filePath(filePath)
{
}

bool CSVFileReader::ReadCSV()
{
    CStdioFile file;
    CFileException fileException;
    if (!file.Open(m_filePath, CFile::modeRead | CFile::typeText, &fileException))
    {
        AfxMessageBox(_T("Error while opening file for reading!"), MB_ICONERROR);
        return false;
    }

    CString line;
    while (file.ReadString(line))
    {
        std::vector<std::string> row;

        // Bezpoœrednia konwersja CString do std::string
        CT2CA pszConvertedAnsiString(line);
        std::string lineStdString(pszConvertedAnsiString);

        std::stringstream ss(lineStdString);
        std::string cell;

        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }
        m_data.push_back(row);
    }
    file.Close();
    AfxMessageBox(_T("Data imported successfully"), MB_ICONINFORMATION);
    return true;
}

std::vector<std::vector<std::string>> CSVFileReader::GetData() const
{
    return m_data;
}
