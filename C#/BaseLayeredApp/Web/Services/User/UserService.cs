using System.Collections.Generic;
using System.Linq;
using Data.User;
using Web.Models;

namespace Web.Services.User
{
    public class UserService : IUserService
    {
        private readonly IUserRepository _userRepository;
        
        public UserService()
        {
            _userRepository = new UserRepository();
        }

        public List<UserViewModel> GetAllUsers()
        {
            return _userRepository.GetAllUsers().Select(u => new UserViewModel
            {
                Email = u.Email,
                Login = u.Login
            }).ToList();
        }

        public UserViewModel GetByLogin(string login)
        {
            var user =  _userRepository.GetAllUsers().FirstOrDefault(u => u.Login == login);
            if (user == null)
            {
                return null;
            }

            return new UserViewModel
            {
                Email = user.Email,
                Login = user.Login
            };
        }
    }
}