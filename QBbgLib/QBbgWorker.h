#ifdef NOTCOMPILED
#ifndef QBbgWorker_h__
#define QBbgWorker_h__

#include "QBbgProjectGlobals.h"

#include "QBbgRequestGroup.h"
#include <QObject>
#include <QMap>
#include <QHash>
#include <QScopedPointer>
namespace QBbgLib {
    class QBbgWorkerPrivate;
	class QBBG_EXPORT QBbgWorker : public QObject
	{
		Q_OBJECT
    private:
        Q_DECLARE_PRIVATE(QBbgWorker)
        QBbgWorkerPrivate* d_ptr;
	public:
		QBbgWorker(QObject* parent =NULL);
		virtual ~QBbgWorker();
        /*!
        \brief The address of the Bloomberg server
        \details This property stores the address of the Bloomberg server.<br/>By default it's set on localhost to run on machines that are Bloomberg terminals.
        \sa setServerAddress
        */
		const QString& serverAddress() const;
        /*!
        \brief Sets the address of the Bloomberg server
        \sa serverAddress
        */
		void setServerAddress(const QString& val);
        /*!
        \brief Port used to connect to the Bloomberg Server
        \details This property stores the port used to connect to the Bloomberg server.<br/>By default it's set to 8194.
        \sa setServerPort
        */
		unsigned short serverPort() const;
        /*!
        \brief Sets the port used to connect to the Bloomberg Server
        \sa serverPort
        */
		void setServerPort(unsigned short val);
        /*!
        \brief Sets the request that has to be sent to Bloomberg
        \details This sets the request that should be sent to Bloomberg, the individual data requests will be split automatically in the most efficient way and sent.<br/>If a request was already sent and is still pending answer from Bloomberg, this method will do nothing.
        */
		void setRequest(const QBbgRequestGroup& a);
        /*!
        \brief Sends the current request to Bloomberg 
        \details This sends to Bloomberg the request previously set with setRequest.<br/>This method will return only once all results are collected.
        \sa setRequest
        \sa startRequestAsync
        */
		void startRequestSync();
        /*!
        \brief Sets the current request and sends it to Bloomberg
        \details This is equivalent to:
        \code{.cpp}
        setRequest(a); 
        startRequestSync();
        \endcode
        \sa startRequestAsync
        \sa setRequest
        \sa startRequestSync
        */
		void startRequestSync(const QBbgRequestGroup& a);
		const QSingleBbgResult* GetResult(qint64 ID) const;
		const QBbgRequestGroup& GetRequest() const;
		bool isRunning() const;
	public slots:
		void StopRequest();
		void StartRequestAsync();
		void StartRequestAsync(const QBbgRequestGroup& a);
	private:
        QBbgWorker(const QBbgWorker&);
	signals :
		void Recieved(qint64);
		void Progress(qint32);
		void Started();
		void Stopped();
		void Finished();
	};
}
#endif // QBbgWorker_h__
#endif