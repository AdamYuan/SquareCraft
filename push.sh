#!/bin/bash
#git reset --hard
git rm --cached ./*
git add ./*
git commit -m "$(date)"
git push origin master
