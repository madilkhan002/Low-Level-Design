from post import Post
class User:
    def __init__(self,id,name):
        self.id = id
        self.name = name
        self.posts = []
        self.friends = []

    def add_post(self,text):
        new_post = Post(text)
        self.posts.append(new_post)

    def add_friend(self,user):
        self.friends.append(user)

    def get_all_posts(self):
        print(f"{self.name} Posts : ")
        for post in self.posts:
            print(post.pid,'-',post.text)

    def get_all_friend(self):
        print(f"{self.name} Friends : ")
        for i,friend in enumerate(self.friends):
            print(i+1,'-',friend.name)

    def add_comment(self,id,text,user_controller):
        for _user in user_controller.users:
            for post in _user.posts:
                if post.pid == id:
                    post.add_comment(text,self)
    def get_all_comment(self,id,user_controller):
        for _user in user_controller.users:
            for post in _user.posts:
                if post.pid == id:
                    print('Post : ',post.text)
                    print('Comments : ')
                    post.get_all_comments()

