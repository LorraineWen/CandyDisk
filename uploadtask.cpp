#include "uploadtask.h"
#include <QFileInfo>
#include "util.h"
UploadTask*UploadTask::uploadtask =new UploadTask;
UploadTask::UploadTask() {}
UploadTask*UploadTask::getInstance()
{
    return uploadtask;
}
int UploadTask::appendUploadTask(QString filepath)
{
    qint64 filesize=QFileInfo(filepath).size();
    if(filesize>300*1024*1024)
    {
        return -1;
    }
    UploadFileInfo *uploadfileinfo=new UploadFileInfo;
    int pos = filepath.lastIndexOf("/", -1) + 1;
    uploadfileinfo->filename = filepath.mid(pos);
    uploadfileinfo->filepath = filepath;
    uploadfileinfo->size = filesize;
    uploadfileinfo->md5 = Util::get_instance()->getFileMd5(filepath);
    uploadfilelist.append(uploadfileinfo);
    return 0;
}
UploadFileInfo* UploadTask::takeTask()
{
    UploadFileInfo *f=NULL;
    if(uploadfilelist.size())f=uploadfilelist.at(0);
    return f;
}
bool UploadTask::isEmpty()
{
    return uploadfilelist.isEmpty();
}
void UploadTask::deleteUploadTask()
{
    UploadFileInfo *f=uploadfilelist.takeAt(0);
    if(f!=NULL)    delete f;
}
