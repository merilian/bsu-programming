using System.Collections.Generic;

namespace Data.User
{
    public interface IUserRepository
    {
        List<User> GetAllUsers();
    }
}