#ifndef _WORKER_HPP_
#define _WORKER_HPP_

#include "zhelpers.hpp"
#include "utils.hpp"


/**
 * @class Base class for workers
 */
class Worker {
public:
  explicit Worker(boost::shared_ptr<zmq::context_t> ctx,
                  const std::string& uriInproc, int id)
    : ctx_(ctx), uriInproc_(uriInproc), id_(id) {}

  void
  operator()() {
    Socket socket(*ctx_, ZMQ_REP);
    socket.connect(uriInproc_.c_str());
    std::string data;

    while (true) {
      data.clear();
      try {
        data = socket.get();
      } catch (zmq::error_t &error) {
        std::cerr << boost::format("E: %1%\n") % error.what();
        continue;
      }
      std::cout << boost::format("Worker %1% | Recv: %2% | Size: %3%\n")% id_ % data % data.length();
      // Deserialize and call Method
      if (!data.empty()) {
        std::string resultSerialized = doCall(data);
        socket.send(resultSerialized);
      }
    }
  }


protected:
  virtual std::string
  doCall(std::string& data) = 0;

  boost::shared_ptr<zmq::context_t> ctx_; /**< zmq context */
  std::string uriInproc_; /**< worker id */
  int id_; /**< worker id */
};


template<typename WorkerType,
         typename WorkerParam>
int
serverWorkerSockets(const std::string& serverUri,
                    const std::string& workerUri,
                    int nbThreads,
                    WorkerParam params) {
  boost::shared_ptr<zmq::context_t> context(new zmq::context_t(1));
  zmq::socket_t socket_server(*context, ZMQ_ROUTER);
  zmq::socket_t socket_workers(*context, ZMQ_DEALER);

  // bind the sockets
  try {
    socket_server.bind(serverUri.c_str());
  } catch (const zmq::error_t& e) {
    std::cerr << boost::format("E: zmq socket_server (%1%) binding failed (%2%)\n") % serverUri % e.what();
    return 1;
  }

  try {
    socket_workers.bind(workerUri.c_str());
  } catch (const zmq::error_t& e) {
    std::cerr << boost::format("E: zmq socket_worker (%1%) binding failed (%2%)\n") % workerUri % e.what();
    return 1;
  }

  std::cout << boost::format("I: listening... (%1%)\n") % serverUri;

  // Create our pool of threads
  ThreadPool pool(nbThreads);
  for (int i = 0; i < nbThreads; ++i) {
    pool.submit(WorkerType(context, workerUri, i, params));
  }

  // connect our workers threads to our server via a queue
  do {
    try {
      zmq::device(ZMQ_QUEUE, socket_server, socket_workers);
      break;
    } catch (const zmq::error_t& e) {
      if (EINTR == e.num()) {
        continue;
      } else {
        std::cerr << boost::format("E: zmq device creation failed (%1%)\n") % e.what();
        return 1;
      }
    }
  } while(true);

  return 0;
}


#endif /* _WORKER_HPP_ */