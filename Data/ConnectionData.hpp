

#ifndef ConnectionData_hpp
#define ConnectionData_hpp

#include "cocos2d.h"
class DataBuilder;

class connection_array;

class connection_object;

struct connection_data_wrapper
{
    enum class type
    {
        _int,
        _bool,
        _short,
        _byte,
        _long,
        _double,
        _float,
        _string,
        _object,
        _array,
        _int_array,
        _bool_array,
        _short_array,
        _byte_array,
        _long_array,
        _double_array,
        _float_array,
        _string_array
    };
    
    bool isInt() { return _type == type::_int; }
    bool isBool() { return _type == type::_bool; }
    bool isShort() { return _type == type::_short; }
    bool isByte() { return _type == type::_byte; }
    bool isLong() { return _type == type::_long; }
    bool isDouble() { return _type == type::_double; }
    bool isFloat() { return _type == type::_float; }
    bool isString() { return _type == type::_string; }
    bool isObject() { return _type == type::_object; }
    bool isArray() { return _type == type::_array; }
    bool isIntArray() { return _type == type::_int_array; }
    bool isBoolArray() { return _type == type::_bool_array; }
    bool isShortArray() { return _type == type::_short_array; }
    bool isByteArray() { return _type == type::_byte_array; }
    bool isLongArray() { return _type == type::_long_array; }
    bool isDoubleArray() { return _type == type::_double_array; }
    bool isFloatArray() { return _type == type::_float_array; }
    bool isStringArray() { return _type == type::_string_array; }
    
    connection_data_wrapper(std::shared_ptr<void> pdata, type ptype)
    {
        data = std::shared_ptr<void>(pdata);
        _type = ptype;
    }
    
    std::shared_ptr<void> data;
    type _type;
};

class connection_object
{
public:
    
    connection_object()
    {
        _map = std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<connection_data_wrapper>>>(new std::unordered_map<std::string, std::shared_ptr<connection_data_wrapper>>);
    }
    
    connection_object(const connection_object& object)
    {
        _map = std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<connection_data_wrapper>>>(object._map);
    }
    
    connection_object& operator=(const connection_object& object)
    {
        if (this != &object)
        {
            _map = std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<connection_data_wrapper>>>(object._map);
        }
        return *this;
    }
    
	void Dump();

    /*
     *                          GET SINGLE DATA
     */
	int getInt(const std::string& key)
	{
		return (int)(*std::static_pointer_cast<long int>((*_map)[key]->data));
	}

    long int getLongInt(const std::string& key)
    {
        return *std::static_pointer_cast<long int>((*_map)[key]->data);
    }
    
    long long getLong(const std::string& key)
    {
        return *std::static_pointer_cast<long long>((*_map)[key]->data);
    }
    
    std::shared_ptr<std::string> getString(const std::string& key)
    {
        return std::static_pointer_cast<std::string>((*_map)[key]->data);
    }
    
    bool getBool(const std::string& key)
    {
        return *std::static_pointer_cast<bool>((*_map)[key]->data);
    }
    
    short int getShort(const std::string& key)
    {
        return *std::static_pointer_cast<short int>((*_map)[key]->data);
    }
    
    double getDouble(const std::string& key)
    {
        return *std::static_pointer_cast<double>((*_map)[key]->data);
    }
    
    float getFloat(const std::string& key)
    {
        return *std::static_pointer_cast<float>((*_map)[key]->data);
    }
    
    unsigned char getByte(const std::string& key)
    {
        return *std::static_pointer_cast<unsigned char>((*_map)[key]->data);
    }
    
    std::shared_ptr<connection_object> getObject(const std::string& key)
    {
        return std::static_pointer_cast<connection_object>((*_map)[key]->data);
    }
    
    std::shared_ptr<connection_array> getArray(const std::string& key)
    {
        return std::static_pointer_cast<connection_array>((*_map)[key]->data);
    }
    
    /*
     *                          GET ARRAY DATA
     */
    std::shared_ptr<std::vector<long int>> getIntArray(const std::string& key)
    {
        return std::static_pointer_cast<std::vector<long int>>((*_map)[key]->data);
    }
    
    std::shared_ptr<std::vector<long long>> getLongArray(const std::string& key)
    {
        return std::static_pointer_cast<std::vector<long long>>((*_map)[key]->data);
    }

    std::shared_ptr<std::vector<float>> getFloatArray(const std::string& key)
    {
        return std::static_pointer_cast<std::vector<float>>((*_map)[key]->data);
    }

    std::shared_ptr<std::vector<double>> getDoubleArray(const std::string& key)
    {
        return std::static_pointer_cast<std::vector<double>>((*_map)[key]->data);
    }
    
    std::shared_ptr<std::vector<unsigned char>> getByteArray(const std::string& key)
    {
        return std::static_pointer_cast<std::vector<unsigned char>>((*_map)[key]->data);
    }

    std::shared_ptr<std::vector<short int>> getShortArray(const std::string& key)
    {
        return std::static_pointer_cast<std::vector<short int>>((*_map)[key]->data);
    }

    std::shared_ptr<std::vector<bool>> getBoolArray(const std::string& key)
    {
        return std::static_pointer_cast<std::vector<bool>>((*_map)[key]->data);
    }

    std::shared_ptr<std::vector<std::string>> getStringArray(const std::string& key)
    {
        return std::static_pointer_cast<std::vector<std::string>>((*_map)[key]->data);
    }
    
    
//    /*
//     *                              SET DATA
//     */

    void putInt(const std::string& key, const long int& value)
    {
        put<long int>(key, value, connection_data_wrapper::type::_int);
    }

    void putLong(const std::string& key, const long long& value)
    {
        put<long long>(key, value, connection_data_wrapper::type::_long);
    }
    
    void putDouble(const std::string& key, const double& value)
    {
        put<double>(key, value, connection_data_wrapper::type::_double);
    }
    
    void putFloat(const std::string& key, const float& value)
    {
        put<float>(key, value, connection_data_wrapper::type::_float);
    }
    
    void putBool(const std::string& key, const bool& value)
    {
        put<bool>(key, value, connection_data_wrapper::type::_bool);
    }
    
    void putShort(const std::string& key, const short int& value)
    {
        put<short int>(key, value, connection_data_wrapper::type::_short);
    }
    
    void putByte(const std::string& key, const unsigned char& value)
    {
        put<unsigned char>(key, value, connection_data_wrapper::type::_byte);
    }
    
    void putString(const std::string& key, const std::string& value)
    {
        put<std::string>(key, value, connection_data_wrapper::type::_string);
    }
    
    void putObject(const std::string& key, const connection_object& value)
    {
        put<connection_object>(key, value, connection_data_wrapper::type::_object);
    }
    
    void putArray(const std::string& key, const connection_array& value)
    {
        put<connection_array>(key, value, connection_data_wrapper::type::_array);
    }

    /*
    *                              SET ARRAY DATA
    */
    
    void putIntArray(const std::string& key, const std::vector<long int>& value)
    {
        put<std::vector<long int>>(key, value, connection_data_wrapper::type::_int_array);
    }

    void putLongArray(const std::string& key, const std::vector<long long>& value)
    {
        put<std::vector<long long>>(key, value, connection_data_wrapper::type::_long_array);
    }

    void putShortArray(const std::string& key, const std::vector<short int>& value)
    {
        put<std::vector<short int>>(key, value, connection_data_wrapper::type::_short_array);
    }

    void putByteArray(const std::string& key, const std::vector<unsigned char>& value)
    {
        put<std::vector<unsigned char>>(key, value, connection_data_wrapper::type::_byte_array);
    }

    void putDoubleArray(const std::string& key, const std::vector<double>& value)
    {
        put<std::vector<double>>(key, value, connection_data_wrapper::type::_double_array);
    }

    void putFloatArray(const std::string& key, const std::vector<float>& value)
    {
        put<std::vector<float>>(key, value, connection_data_wrapper::type::_float_array);
    }

    void putBoolArray(const std::string& key, const std::vector<bool>& value)
    {
        put<std::vector<bool>>(key, value, connection_data_wrapper::type::_bool_array);
    }

    void putStringArray(const std::string& key, const std::vector<std::string>& value)
    {
        put<std::vector<std::string>>(key, value, connection_data_wrapper::type::_string_array);
    }

    bool containsKey(const std::string& key)
    {
        return _map->find(key) != _map->end();
    }
    
    template<typename T> void put(const std::string& key, const T& value, connection_data_wrapper::type ptype)
    {
        _map->insert(std::make_pair(key, std::shared_ptr<connection_data_wrapper>(new connection_data_wrapper(std::shared_ptr<void>(new T(value)), ptype))));
    }
    
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<connection_data_wrapper>>> _map;
    
};

class connection_array
{
public:
    bool getBool(int index)
    {
        return *std::static_pointer_cast<bool>(_array[index]->data);
    }
    
    std::shared_ptr<std::vector<bool>> getBoolArray(int index)
    {
        return std::static_pointer_cast<std::vector<bool>>(_array[index]->data);
    }

    long int getInt(int index)
    {
        return *std::static_pointer_cast<long int>(_array[index]->data);
    }

    std::shared_ptr<std::vector<long int>> getIntArray(int index)
    {
        return std::static_pointer_cast<std::vector<long int>>(_array[index]->data);
    }

    double getDouble(int index)
    {
        return *std::static_pointer_cast<double>(_array[index]->data);
    }

    std::shared_ptr<std::vector<double>> getDoubleArray(int index)
    {
        return std::static_pointer_cast<std::vector<double>>(_array[index]->data);
    }

    float getFloat(int index)
    {
        return *std::static_pointer_cast<float>(_array[index]->data);
    }

    std::shared_ptr<std::vector<float>> getFloatArray(int index)
    {
        return std::static_pointer_cast<std::vector<float>>(_array[index]->data);
    }

    long long getLong(int index)
    {
        return *std::static_pointer_cast<long long>(_array[index]->data);
    }

    std::shared_ptr<std::vector<long long>> getLongArray(int index)
    {
        return std::static_pointer_cast<std::vector<long long>>(_array[index]->data);
    }

    short int getShort(int index)
    {
        return *std::static_pointer_cast<short int>(_array[index]->data);
    }

    std::shared_ptr<std::vector<short int>> getShortArray(int index)
    {
        return std::static_pointer_cast<std::vector<short int>>(_array[index]->data);
    }

    unsigned char getByte(int index)
    {
        return *std::static_pointer_cast<unsigned char>(_array[index]->data);
    }

    std::shared_ptr<std::vector<unsigned char>> getByteArray(int index)
    {
        return std::static_pointer_cast<std::vector<unsigned char>>(_array[index]->data);
    }

    std::shared_ptr<std::string> getString(int index)
    {
        return std::static_pointer_cast<std::string>(_array[index]->data);
    }

    std::shared_ptr<std::vector<std::string>> getStringArray(int index)
    {
        return std::static_pointer_cast<std::vector<std::string>>(_array[index]->data);
    }

    std::shared_ptr<connection_object> getObject(int index)
    {
        return std::static_pointer_cast<connection_object>(_array[index]->data);
    }

    std::shared_ptr<connection_array> getArray(int index)
    {
        return std::static_pointer_cast<connection_array>(_array[index]->data);
    }
    
    
    void pushInt(const long int& value)
    {
        put<long int>(value, connection_data_wrapper::type::_int);
    }
    
    void pushBool(const bool& value)
    {
        put<bool>(value, connection_data_wrapper::type::_bool);
    }
    
    void pushShort(const short int& value)
    {
        put<short int>(value, connection_data_wrapper::type::_short);
    }
    
    void pushByte(const unsigned char& value)
    {
        put<unsigned char>(value, connection_data_wrapper::type::_byte);
    }
    
    void pushLong(const long long& value)
    {
        put<long long>(value, connection_data_wrapper::type::_long);
    }
    
    void pushDouble(const double& value)
    {
        put<double>(value, connection_data_wrapper::type::_double);
    }
    
    void pushFloat(const float& value)
    {
        put<float>(value, connection_data_wrapper::type::_float);
    }
    
    void pushString(const std::string& value)
    {
        put<std::string>(value, connection_data_wrapper::type::_string);
    }
    
    void pushObject(const connection_object& value)
    {
        put<connection_object>(value, connection_data_wrapper::type::_object);
    }
    
    void pushArray(const connection_array& value)
    {
        put<connection_array>(value, connection_data_wrapper::type::_array);
    }
    
    void pushIntArray(const std::vector<long int>& value)
    {
        put<std::vector<long int>>(value, connection_data_wrapper::type::_int_array);
    }
    
    void pushBoolArray(const std::vector<bool>& value)
    {
        put<std::vector<bool>>(value, connection_data_wrapper::type::_bool_array);
    }
    
    void pushByteArray(const std::vector<unsigned char>& value)
    {
        put<std::vector<unsigned char>>(value, connection_data_wrapper::type::_byte_array);
    }
    
    void pushShortArray(const std::vector<short int>& value)
    {
        put<std::vector<short int>>(value, connection_data_wrapper::type::_short_array);
    }
    
    void pushLongArray(const std::vector<long long>& value)
    {
        put<std::vector<long long>>(value, connection_data_wrapper::type::_long_array);
    }
    
    void pushDoubleArray(const std::vector<double>& value)
    {
        put<std::vector<double>>(value, connection_data_wrapper::type::_double_array);
    }
    
    void pushFloatArray(const std::vector<float>& value)
    {
        put<std::vector<float>>(value, connection_data_wrapper::type::_float_array);
    }
    
    void pushStringArray(const std::vector<std::string>& value)
    {
        put<std::vector<std::string>>(value, connection_data_wrapper::type::_string_array);
    }
    
    template<typename T> void put(const T& value, connection_data_wrapper::type ptype)
    {
        _array.push_back(std::shared_ptr<connection_data_wrapper>(new connection_data_wrapper(std::shared_ptr<void>(new T(value)), ptype)));
    }
    
    long Size()
    {
        return _array.size();
    }
    
    std::vector<std::shared_ptr<connection_data_wrapper>> _array;
};

class DataBuilder {

public :
	static DataBuilder* builder();
	DataBuilder* putString(std::string key, std::string value);
	DataBuilder* putInt(std::string key, int value);
	DataBuilder* putShort(std::string key, short value);
	DataBuilder* putFloat(std::string key, float value);
	DataBuilder* putBool(std::string key, bool value);
	std::shared_ptr<connection_object> build();
protected:
	DataBuilder();
	std::shared_ptr<connection_object> _data;
};
#endif /* ConnectionData_hpp */
