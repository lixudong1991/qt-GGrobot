#ifndef LOGIN_DEVICE_INFO_H
#define LOGIN_DEVICE_INFO_H


class Login_device_info
{
public:
    Login_device_info();
    void setLoginID(long l)
    {
        lLoginID=l;
    }

    long getLoginID()const
    {
        return lLoginID;
    }
private:
    long  lLoginID=-1;
};

#endif // USER_H
