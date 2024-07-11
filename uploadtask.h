#ifndef UPLOADTASK_H
#define UPLOADTASK_H
#include<QString>
#include<QList>
struct UploadFileInfo
{
    QString md5;
    QString filename;
    QString filepath;
    qint64 size;
};
class UploadTask
{
public:
    static UploadTask*getInstance();
    int appendUploadTask(QString filepath);
    UploadFileInfo* takeTask();
    bool isEmpty();
    void deleteUploadTask();
private: UploadTask();
    ~UploadTask();
    static UploadTask*uploadtask;
    QList<UploadFileInfo*>uploadfilelist;
};

#endif // UPLOADTASK_H
