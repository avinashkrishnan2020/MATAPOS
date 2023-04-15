#ifndef DATABASE_H
#define DATABASE_H

#include "customer.h"
#include "stock.h"
#include "barcodereader.h"
#include "databasecallback.h"
#include "cart.h"


#include <QSqlDatabase>
#include <QtSql>
#include <QString>
#include <memory>

class Database {
	
	public:

		static std::unique_ptr<Database> getDatabaseInstance();
		void createCustomerTable();
		void createStockTable();

		void registerCallback(DatabaseCallback* clientCallbackPtr);

		void queryCustomerDetails(std::string uniqueId);
		void queryItemDetails(std::string uniqueId);
		void checkoutCustomer(Cart cart);
		void debitTotal(std::string customerId, float totalCost)

		void connOpen();
		void connClose();

		/**
		 * BarcodeReader callback implementation	
		 * */
		struct UniqueIdAvailableCallback: BarcodeReaderCallback {
			Database* databasePtr = nullptr;
			public:
				void uniqueIdAvailable(std::string uniqueId, std::string flow) {
					if(nullptr != databasePtr) {
						if(flow == "customer_identification") {
							databasePtr -> queryCustomerDetails(uniqueId);
						} else {
							databasePtr -> queryItemDetails(uniqueId);
						}
					}	
				}
		};

		UniqueIdAvailableCallback uniqueIdAvailableCallback;
		DatabaseCallback* databaseCallbackPtr = nullptr;

	private:
		Database();
		~Database();
		
		Customer prepareCustomerObj(QSqlQuery query);
		Stock prepareItemObj(QSqlQuery query);
		QSqlDatabase mataposDb;
		QString databasetype;
		QString databasepath;

};
#endif
