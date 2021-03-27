using System.Collections.Generic;
using System.Linq;

namespace Data.User
{
    public class UserRepository : IUserRepository
    {
        private readonly DbContext _dbContext;
        
        public UserRepository()
        {
            _dbContext = new DbContext();
        }

        public List<User> GetAllUsers()
        {
            return _dbContext.Users.Select(u => new User
            {
                Email = u.Email,
                Login = u.Login
            }).ToList();
        }
    }
}