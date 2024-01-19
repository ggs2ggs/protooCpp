#include "Peer.h"
#include "Message.h"

using namespace std;
using namespace nlohmann;

namespace protoo {

	Peer::Peer(string url) {
		m_closed = false;
		m_connected = false;
		//自己new一个transport
		m_pTransport.reset(new WebSocketTransport(url, this));
		//m_pTransport.reset(new WebSocketTransport(url, json(), this));

	}
	Peer::~Peer() {
		if(m_pTransport.get()){
			m_pTransport->close();
		}
	}

	bool Peer::closed()
	{
		return m_closed;
	}

	void Peer::close()
	{
		if (m_closed) {
			return;
		}
		if(m_pTransport.get()){
			m_pTransport->close();
		}
	}

	bool Peer::connected() {
		return m_connected;
	}

	json Peer::data() {
		return m_data;
	}

	void Peer::setData(json datax) {
		//TODO
	}

	//void Peer::requestTest(string method, json data) {
	//    auto request = Message::createRequest(method, data);
	//    std::cout << "[Peer] send a new request id=:" << request["id"].get<int>() << " method=" << method << endl;
	//    //会进入到uWS的线程发送
	//    std::promise<json> promise;
	//    this->m_pTransport->send(request);//just like await    
	//}

	std::future<json> Peer::request(string method, json data) {
		auto request = Message::createRequest(method, data);
		auto id = request["id"].get<int>();
		std::cout << "[Peer] send a new request id=:" << request["id"].get<int>() << " method=" << method << endl;
		auto promise = std::make_shared<std::promise<json>>();
		auto future = promise->get_future();
		//存储promise 并计划一个超时任务
		m_promises[id] = promise;
		

	}

	void Peer::notify(string method, json data) {
		auto request = Message::createNotification(method, data);
		//this->m_pTransport->send(request);
	}


	void Peer::onOpen() {
		std::cout<<"[Peer] onOpen!"<<std::endl;
		m_pTransport->send(json::parse("{\"type\":\"login\",\"data\":{\"username\":\"test\",\"password\":\"test\"}}"));
	}

	void Peer::onClosed() {

	}

	void Peer::onMessage(json message) {
       std::cout<<"[Peer] onMessage:"<<message.dump()<<std::endl;
	}

	void Peer::onDisconnected() {

	}

	void Peer::onFailed() {
// 		if (this->m_closed)
// 			return;
// #if PROTOO_LOG_ENABLE
// 		std::cout << "[Peer] emit failed\n" << endl;
// #endif
// 		this->m_connected = false;
// 		this->m_emitter.emit("failed", nullptr);
	}

	void Peer::handleRequest(json request) {
// 		std::shared_ptr<PROTOO_MSG> pmsg(new PROTOO_MSG);
// 		//message
// 		pmsg->message = request;
// #if PROTOO_LOG_ENABLE
// 		std::cout << "[Peer] handleRequest from server request=" << request.dump(4) << endl;
// #endif
// 		//accept
// 		pmsg->accept = [&, request](json data) {
// 			std::cout << "[Peer] handleRequest accept" << request.dump(4) << endl;
// 			auto response = Message::createSuccessResponse(request, data);
// 			this->m_pTransport->send(response);
// 		};
// 		//reject
// 		pmsg->reject = [&, request](int errorCode, std::string errorReason) {
// 			auto response = Message::createErrorResponse(request, errorCode, errorReason);
// 			this->m_pTransport->send(response);

// 		};
// 		m_emitter.emit("request", pmsg);
	}

	void Peer::handleResponse(json response) {

	}

	void Peer::handleNotification(json notification) {
		// std::shared_ptr<PROTOO_MSG> pmsg(new PROTOO_MSG);
		// pmsg->message = notification;
		// this->m_emitter.emit("notification", pmsg);
	}
}
