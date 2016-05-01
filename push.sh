#!/bin/bash
#git reset --hard
git rm --cached ./*
git add ./*
#git rm --cached ./push.sh
git commit -m "$(date)"
git push origin master
