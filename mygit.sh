git init

git add .

git commit -m "Add attachments"
git remote add origin https://github.com/GeoKylin/8KeyMCU51.git

git pull origin master --allow-unrelated-histories
git push -u origin master
