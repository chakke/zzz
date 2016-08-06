//
//  ConnectionController.hpp
//  GameBai69
//
//  Created by Manh Tran on 2/20/16.
//
//

#ifndef ConnectionController_hpp
#define ConnectionController_hpp

#include "../../AppController/Controller.hpp"
#include "../../Game/GameModel/User.hpp"

typedef std::function<void(const std::string& result)> OnRegisterCallback;
typedef std::function<void(const std::string& result)> OnLoginCallback;
typedef std::function<void()> OnMaintainanceCallback;

class ConnectionController : public Controller
{
private:
    CREATE_FUNC(ConnectionController);
public:
    
    static ConnectionController* getInstance();
    
    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);
    
    virtual void listen(Observer* sender, cocos2d::Ref* ref);
    
    virtual void setLoginCallback(const OnLoginCallback& callback);

	virtual void setRegisterCallback(const OnRegisterCallback& callback);
    
    virtual void setMaintainanceCallback(const OnMaintainanceCallback& callback);
    
    const OnLoginCallback& getLoginCallback() {return _loginCallback;}
	const OnRegisterCallback& getRegisterCallback() { return _registerCallback; }
    const OnMaintainanceCallback& getMaintainanceCallback() {return _maintainanceCallback;}
    
    void disconnect(bool removeUserNameAndPass);
    void login(const game_model::user_type& type, const std::string& account, const std::string& password);
    void registerAccount(const std::string& account, const std::string& password);
    void get_user_info();
    
    std::string _current_room;
private:
    OnLoginCallback _loginCallback;
	OnRegisterCallback _registerCallback;
    OnMaintainanceCallback _maintainanceCallback;
};

#endif /* ConnectionController_hpp */
