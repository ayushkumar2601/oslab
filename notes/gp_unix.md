Sure — I’ve removed the excessive blank lines/vertical spacing while keeping the content unchanged and copy-pasteable.

# DAY 1 – UNIX/LINUX GENERAL PURPOSE UTILITIES

## 1. Self-Assessment with General Purpose Utilities

### 1. What is a Directory?

A **directory** is a folder used to organize and store files and other directories.

### 2. Significance of HOME Variable

`HOME` stores the path of the user's **home directory**.

```bash
echo $HOME
```

Example:

```text
/home/user
```

### 3. Operations on Directories

**a) Check current directory**

```bash
pwd
```

**b) Change current directory**

```bash
cd directory_name
```

**c) Create new directory**

```bash
mkdir directory_name
```

Create multiple directories:

```bash
mkdir dir1 dir2 dir3
```

**d) Remove directory**

```bash
rmdir directory_name
```

Remove multiple empty directories:

```bash
rmdir dir1 dir2
```

For a non-empty directory:

```bash
rm -r directory_name
```

### 4. Absolute and Relative Pathnames

**Absolute Path:** Complete path starting from `/`.

```bash
/home/user/Documents/file.txt
```

**Relative Path:** Path specified with respect to the current directory.

```bash
Documents/file.txt
```

### 5. What is a Command?

A **command** is an instruction given to the operating system through the terminal to perform a specific task.
Example:

```bash
ls
```

### 6. What is `ls` Command?

`ls` displays files and directories in the current directory.

```bash
ls
ls -l
ls -a
```

* `-l` → detailed information
* `-a` → shows hidden files

### 7. How to Switch Directories?

Use the `cd` command.

```bash
cd Documents
cd ..
cd ~
```

* `..` → parent directory
* `~` → home directory

### 8. Display the Current User

```bash
whoami
```

### 9. Display OS Name and Version

```bash
uname -a
```

On Linux, a more detailed command is:

```bash
cat /etc/os-release
```

### 10. Display Calendar

Current month:

```bash
cal
```

Specific month:

```bash
cal 9 2026
```

Entire year:

```bash
cal 2026
```

### 11. Display Date and Time

```bash
date
```

Examples:

```bash
date +"%d-%m-%Y"
date +"%H:%M:%S"
date +"%A, %d %B %Y"
```

### 12. Use of `echo`

`echo` displays text or variable values on the terminal.

```bash
echo "Hello World"
echo $HOME
```

# HANDLING ORDINARY FILES

## THE FILE SYSTEM

### 1. The File – What's in a File Name?

A file name identifies a file. It may contain letters, numbers, and special characters.
Example:

```text
program.c
notes.txt
```

The extension such as `.c` or `.txt` usually indicates the file type.

### 2. Display, Create, Copy, Move, Delete and Rename Files

**Display contents**

```bash
cat file.txt
```

**Create a file**

```bash
touch file.txt
```

**Copy a file**

```bash
cp file.txt copy.txt
```

**Move a file**

```bash
mv file.txt Documents/
```

**Rename a file**

```bash
mv old.txt new.txt
```

**Delete a file**

```bash
rm file.txt
```

### 3. Count Lines, Words and Characters

```bash
wc file.txt
```

Output gives:

```text
Lines  Words  Characters
```

Individual counts:

```bash
wc -l file.txt    # Lines
wc -w file.txt    # Words
wc -c file.txt    # Characters
```

### 4. Comparing Two Files

`diff` compares two files line by line.

```bash
diff file1.txt file2.txt
```

If there is no output, the files are identical.

### 5. What is Common Between Two Files?

`comm` finds common and different lines between **sorted** files.

```bash
comm file1.txt file2.txt
```

Only common lines:

```bash
comm -12 file1.txt file2.txt
```

### 6. Compressing, Decompressing and Archiving Files

**Compress using gzip**

```bash
gzip file.txt
```

**Decompress**

```bash
gunzip file.txt.gz
```

**Create archive**

```bash
tar -cvf files.tar file1.txt file2.txt
```

**Extract archive**

```bash
tar -xvf files.tar
```

**Create compressed archive**

```bash
tar -czvf files.tar.gz file1.txt file2.txt
```

**Extract compressed archive**

```bash
tar -xzvf files.tar.gz
```

# BASIC FILE ATTRIBUTES

## 1. File Ownership

Every file has an **owner** and a **group**.
View ownership:

```bash
ls -l
```

Example:

```text
-rw-r--r-- user group file.txt
```

## 2. File Permissions

Permissions determine who can **read (r), write (w), and execute (x)** a file.

```text
r = Read
w = Write
x = Execute
```

Example:

```text
-rwxr-xr--
```

Change permissions:

```bash
chmod 755 file.txt
```

Change owner:

```bash
chown user file.txt
```

# FILE FILTERS

A **filter** takes input, processes it, and produces output. Common UNIX filters are:

## 1. `head`

Displays the beginning of a file.

```bash
head file.txt
head -n 5 file.txt
```

## 2. `tail`

Displays the end of a file.

```bash
tail file.txt
tail -n 5 file.txt
```

## 3. `cut`

Extracts selected columns/characters.

```bash
cut -d "," -f 1 file.csv
```

`-d` → delimiter
`-f` → field number

## 4. `sort`

Sorts lines alphabetically/numerically.

```bash
sort file.txt
sort -n numbers.txt
```

## 5. `uniq`

Removes consecutive duplicate lines.

```bash
uniq file.txt
```

Usually used with `sort`:

```bash
sort file.txt | uniq
```

## 6. `tr`

Translates or replaces characters.

```bash
tr 'a-z' 'A-Z' < file.txt
```

Converts lowercase letters to uppercase.

## 7. `grep`

Searches for a pattern in a file.

```bash
grep "hello" file.txt
```

Case-insensitive search:

```bash
grep -i "hello" file.txt
```

## 8. `sed`

Used to search, replace and modify text.
Replace first occurrence in each line:

```bash
sed 's/old/new/' file.txt
```

Replace all occurrences:

```bash
sed 's/old/new/g' file.txt
```

# QUICK COMMAND SUMMARY

| Task                 | Command    |
| -------------------- | ---------- |
| Current directory    | `pwd`      |
| List files           | `ls`       |
| Change directory     | `cd`       |
| Create directory     | `mkdir`    |
| Remove directory     | `rmdir`    |
| Current user         | `whoami`   |
| OS information       | `uname -a` |
| Calendar             | `cal`      |
| Date/time            | `date`     |
| Display file         | `cat`      |
| Create file          | `touch`    |
| Copy file            | `cp`       |
| Move/Rename          | `mv`       |
| Delete file          | `rm`       |
| Count                | `wc`       |
| Compare              | `diff`     |
| Common lines         | `comm`     |
| Compress             | `gzip`     |
| Archive              | `tar`      |
| File permissions     | `chmod`    |
| Beginning of file    | `head`     |
| End of file          | `tail`     |
| Extract columns      | `cut`      |
| Sort                 | `sort`     |
| Remove duplicates    | `uniq`     |
| Translate characters | `tr`       |
| Search text          | `grep`     |
| Edit/filter text     | `sed`      |
