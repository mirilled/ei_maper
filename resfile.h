#ifndef RESFILE_H
#define RESFILE_H
#include <QString>
#include <QVector>
#include <QFile>
#include <QDateTime>
#include <QMap>
#include <QBuffer>
#include <QDataStream>

#pragma pack(push, 1)
struct ResFileHeader
{
    uint Signature;
    uint TableSize;
    uint TableOffset;
    uint NamesLenght;

    friend QDataStream& operator>> (QDataStream &st, ResFileHeader &head)
    {
        return st >> head.Signature >> head.TableSize >> head.TableOffset >>
                     head.NamesLenght;
    }

    friend QDataStream& operator<< (QDataStream &st, ResFileHeader const &head)
    {
        return st << head.Signature << head.TableSize << head.TableOffset <<
                     head.NamesLenght;
    }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ResFileHashTableEntry
{
    uint NextIndex;
    uint DataSize;
    uint DataOffset;
    uint LastWriteTime;
    ushort NameLength;
    uint NameOffset;

    friend QDataStream& operator>> (QDataStream &st, ResFileHashTableEntry &entry)
    {
        return st >> entry.NextIndex >> entry.DataSize >> entry.DataOffset >>
                     entry.LastWriteTime >> entry.NameLength >> entry.NameOffset;
    }

    friend QDataStream& operator<< (QDataStream &st, ResFileHashTableEntry const &entry)
    {
        return st << entry.NextIndex << entry.DataSize << entry.DataOffset <<
                     entry.LastWriteTime << entry.NameLength << entry.NameOffset;
    }
};
#pragma pack(pop)

struct ResFileEntry
{
    QString FileName;
    long Position;
    int Size;
    QDateTime LastWriteTime;
};

class ResFile
{
public:
    ResFile(QString& path);
    ~ResFile();
    ResFileHeader Header;
    QMap<QString, ResFileEntry>& GetFiles(QDataStream& stream);
    void AddFile(QString& name, QDateTime time);
private:
    static const uint Signature =  0x019CE23C;
    qint64 StreamStartPosition;
    //QDataStream* Stream;
    QByteArray Buffer;
    QVector<ResFileEntry> Entries;
    QMap<QString, QByteArray> bufferOfFiles;

    void CompletePreviousFile();
    void WriteAlign();
    static QMap<QString, ResFileEntry>& BuildFileTableDictonary(
            QVector<ResFileHashTableEntry>& fileTable, long offsetStream,
            long streamLength, QString& names);
    static QBuffer& ReadNamesByffer();
    static void BuildResHashTable(
            QVector<ResFileEntry>& entries, long headerPositon,
            QVector<ResFileHashTableEntry> hashTable, QBuffer& namesBuffer);
    static ushort AppendNamesBuffer(QBuffer& buffer, QString& name);

};

#endif // RESFILE_H
