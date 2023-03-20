#ifndef DATA_RETRIEVER_H
#define DATA_RETRIEVER_H

class DataRetriever {
	
public:

	DataRetriever();

	~DataRetriever();
	
	void startDb();
	
	void stopDb();

	void displayCustomerDetails();

	void setItemDetails();

	struct DataRetrieverCallback: public BarcodeReaderCallback {
		DataRetriever* dataRetrieverPtr = nullptr;

		virtual void customerIdAvailable(std::string uniqueId, std::string applicationState) {
			if(nullptr != dataRetrieverPtr) {
				// call method to display customer details

				// call method to return item details
			}
		}



	}	
}


#endif
