using Microsoft.AspNetCore.Mvc;
using Web.Services.User;

namespace Web.Controllers
{
    public class UserController : Controller
    {
        private readonly IUserService _userService;

        public UserController()
        {
            _userService = new UserService();
        }
        
        public IActionResult Index()
        {
            var users = _userService.GetAllUsers();
            return View(users);
        }
        
        public IActionResult ShowPersonalPage(string login)
        {
            var user = _userService.GetByLogin(login);
            return View(user);
        }
    }
}