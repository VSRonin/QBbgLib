#ifndef QSingleBbgResult_h__
#define QSingleBbgResult_h__
#include "QBbgProjectGlobals.h"
#include "QBbgGenerals.h"
#include <QList>
#include <QString>
#include <QDate>
namespace QBbgLib {
	class QSingleBbgResultPrivate;
	class QBbgWorker;
    class QBbgWorkerPrivate;
	class QBBG_EXPORT QSingleBbgResult
	{
    private:
        Q_DECLARE_PRIVATE(QSingleBbgResult)
        QSingleBbgResultPrivate* d_ptr;
	public:
		QSingleBbgResult();
		QSingleBbgResult(const QSingleBbgResult& a);
		QSingleBbgResult& operator=(const QSingleBbgResult& a);
		virtual ~QSingleBbgResult();
		bool IsEmpty() const;
		bool HasString() const;
		bool HasDate() const;
		bool HasDouble() const;
        bool HasTable() const;
		bool HasValue()const;
		const QString& GetHeader()const;
		QString GetString()const;
		QDate GetDate() const;
		double GetDouble()const;
		qint32 GetNumRows() const;
		qint32 GetNumCols() const;
		const QSingleBbgResult* GetTableResult(quint32 r, quint32 c) const;
	protected:
        void SetValue(const QString& val, const QString& Header = QString());
        void AddValueRow(const QList<QString>& val, const QList<QString>& Headers = QList<QString>());
		void SetHeader(const QString& Header = QString());
		friend class QBbgWorker;
        friend class QBbgWorkerPrivate;
	};
}
#endif // QSingleBbgResult_h__