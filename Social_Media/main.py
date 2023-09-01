from user import User
from userController import UserController

# user contoller object
user_controller = UserController()

user1 = User(1,'Adil')
user_controller.add_user(user1)
user2 = User(2,'Ali')
user_controller.add_user(user2)
user3 = User(3,'Dawood')
user_controller.add_user(user3)
user4 = User(4,'Sheraz')
user_controller.add_user(user4)

user1.add_post("Hi Everyone......")
user1.add_post("I'm not sure.....")
user1.add_friend(user2)
user1.add_friend(user3)

user1.add_comment(2,"LOL !!!",user_controller)
user1.add_comment(2,"LOL(2) !!!",user_controller)
user2.add_comment(2,"LOL(3) !!!",user_controller)
print(user_controller)

user1.get_all_posts()
user1.get_all_friend()
user1.get_all_comment(2,user_controller)
