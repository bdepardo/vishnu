#ifndef LOCALFILEPROXY_HH
#define LOCALFILEPROXY_HH

#include <string>


#include "SessionProxy.hpp"

#include "FileProxy.hpp"

/* Local implementation of a DIET file. */

class LocalFileProxy : public FileProxy {
private:
  mutable bool upToDate;
public:
  LocalFileProxy();
  LocalFileProxy(const SessionProxy& sessionProxy,const std::string& path);
  LocalFileProxy(const LocalFileProxy& file);
  
  LocalFileProxy& operator=(const LocalFileProxy& file);
  
  virtual bool isUpToDate() const;
  virtual void getInfos() const;
  
  virtual int chgrp(const std::string& group) { }
  virtual int chmod(const mode_t mode) { }
  virtual std::string head(const HeadOfFileOptions& options) { }
  virtual std::string getContent() { }
  virtual int mkfile(const mode_t mode=420) { }
  virtual int mkdir(const mode_t mode=493) { }
  virtual int rm() { }
  virtual int rmdir() { }
  virtual std::string tail(const TailOfFileOptions& options) { }

  virtual int cp(const std::string& dest, const CpFileOptions& options, const std::string& serviceName="FileCopy");

  virtual int mv(const std::string& dest, const CpFileOptions& options);

  virtual std::list<std::string> ls(const LsDirOptions& options) const { }
};

#endif
