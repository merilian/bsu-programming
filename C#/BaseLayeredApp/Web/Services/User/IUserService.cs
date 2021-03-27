using System.Collections.Generic;
using Web.Models;

namespace Web.Services.User
{
    public interface IUserService
    {
        List<UserViewModel> GetAllUsers();
        UserViewModel GetByLogin(string login);
    }
}