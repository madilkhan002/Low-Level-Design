from comment import Comment
from like import Like

class Post:
    id = 1
    def __init__(self,text):
        self.pid = Post.id
        self.text = text
        self.comments = []
        self.likes = []
        Post.id += 1

    def add_comment(self,text,user):
        new_comment = Comment(text,user)
        self.comments.append(new_comment)

    def add_likes(self,user):
        new_like = Like(user)
        self.likes.append(new_like)

    def get_all_comments(self):
        for i,comment in enumerate(self.comments):
            print(i+1 , '-',comment.text)
