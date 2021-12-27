#include <process.hpp>

Process::Process(const std::string & address, const std::string & action) 
            : resolver(ioc), socket(ioc)
            {
                out.open("localversion.html");

                host = address;
                target = action;
            }

void Process::send()
{
    // Резолвим адрес и устанавливаем соединение
    boost::asio::connect(socket, resolver.resolve(host, "80"));

    // Дальше необходимо создать HTTP GET реквест с указанием таргета
    http::request<http::string_body> req(http::verb::get, target, 11);
    // Задаём поля HTTP заголовка
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    
    // Отправляем реквест через приконекченный сокет
    http::write(socket, req);
}

void Process::read()
{
    boost::beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(socket, buffer, res);

    out << res << std::endl;
}

Process::~Process()
{
    // Закрываем соединение
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    out.close();
}