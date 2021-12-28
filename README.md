# Educational Administration Platform Emulator

This is an simple emulator arm to implement
**Educational Administration Platform**
base on terminal user interface
_(TUI, but without GUI)_.

### Session Launch

This idea is **inspired** by **Unix**,
which has known as a multi-users system.

The first time you launch this program,
the default user `root` generated automatily.

Default password of all users are their name,
but you can optionally change it as your perfered.
Just go to **Account settings -> Change your password**,
noted that password must be more than 6 charactor.

### Features

- Different types of users
	- Adminstrators (teachers)
		- Add and delete students
		- Add and delete exam subjects
		- Find student and operation
		- Show all contents of database
	- Normal Users (Students)
		- Show their own's scores
- Account settings
	- Change their password
- Simple Database
- ...

### How to build

For Unix-like users,
simply clone this repository and make:

``` shell
~ > git clone https://github.com/supdrewin/edu_adm_pla_emu.git
~ > cd edu_adm_pla_emu
~/edu_adm_pla_emu > make
```

**NOTE:**
- If you using BSD,
  you should install `bash` before make.
- For macOS users,
  if you don't have Csu,
  don't try to build with `-static`.

For MinGW-w64 (Windows),
replace the `make` with `mingw32-make` work.

Alternately,
you can buid Windows binary under Linux.
Just set the `CXX` environment to your MinGW.

To Cross-Build for another architectures,
make sure you have install their Toolkits,
than change the `CXX`.

``` shell
~ > export CXX=/path/to/your/c++
```

### Contributing

This project has not completed and may need your help.
If you meet BUGs or have a good idea for improve this program,
just open a issue from
[here](https://github.com/supdrewin/edu_adm_pla_emu/issues).
And **PR** is welcome to opend
[here](https://github.com/supdrewin/edu_adm_pla_emu/pulls).
