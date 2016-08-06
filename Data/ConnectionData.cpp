
#include "ConnectionData.hpp"

void connection_object::Dump()
{
	
}

DataBuilder * DataBuilder::builder()
{
	return new DataBuilder();
}

DataBuilder * DataBuilder::putString(std::string key, std::string value)
{
	this->_data->putString(key,value);
	return this;
}

DataBuilder * DataBuilder::putInt(std::string key, int value)
{
	this->_data->putInt(key,value);
	return this;
}

DataBuilder * DataBuilder::putShort(std::string key, short value)
{
	this->_data->putShort(key,value);
	return this;
}

DataBuilder * DataBuilder::putFloat(std::string key, float value)
{
	this->_data->putFloat(key, value);
	return this;
}

DataBuilder * DataBuilder::putBool(std::string key, bool value)
{
	this->_data->putBool(key,value);
	return this;
}

std::shared_ptr<connection_object> DataBuilder::build()
{
	return this->_data;
}

DataBuilder::DataBuilder()
{
	this->_data = std::shared_ptr<connection_object>(new connection_object());
}
