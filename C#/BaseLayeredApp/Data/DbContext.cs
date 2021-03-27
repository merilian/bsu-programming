using System.Collections.Generic;
using Data.DbModels;
using Data.User;

namespace Data
{
    public class DbContext
    {
        public List<UserDbModel> Users = new List<UserDbModel>
        {
            new UserDbModel
            {
                Email = "email1@address.com",
                Login = "Login1"
            },
            new UserDbModel
            {
                Email = "email2@address.com",
                Login = "Login2"
            },
            new UserDbModel
            {
                Email = "email3@address.com",
                Login = "Login3"
            }
        };
    }
}