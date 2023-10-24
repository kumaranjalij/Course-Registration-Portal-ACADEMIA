
//Record Details Getters and Setters.....
int get_next_record(int type){
	struct record myrecord;
	int rfd,rd,res, offset;
	rfd=open("./Record_File/record.txt",O_RDONLY);
	if(rfd==-1){
		perror("Cannot Open File ");
		return -1;
	}
	offset=lseek(rfd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in Record File ");
		return -1;
	}

	/*Setting Lock*/
	struct flock mylock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int rdlock = fcntl(rfd, F_SETLKW, &mylock);
	if(rdlock == -1)
	{
		perror("Error obtaining read lock on Account record!");
		return 0;
	}
	/*...........*/
	rd=read(rfd,&myrecord,sizeof(myrecord));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(rfd, F_SETLK, &mylock);
	/*...........*/
	if(rd<=0){
		perror("Cannot read the file ");
		return -1;
	}
	// Body.................
	switch(type){
	case 0: res=myrecord.new_s;
		break;
	case 1: res=myrecord.new_f;
		break;
	case 2: res=myrecord.new_c;
		break;
	default: return -1;
		break;
	}
	
	
	close(rfd);
	return res;
}

int set_next_record(int type, int next){
	struct record myrecord;
	int rfd,rd,wt, offset;
	//open...
	rfd=open("./Record_File/record.txt",O_RDWR);
	if(rfd==-1){
		perror("Cannot Open File ");
		return 0;
	}
	//read...
	offset=lseek(rfd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in Record File ");
		return 0;
	}

	/*Setting Lock*/
	struct flock mylock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lock = fcntl(rfd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining read lock on Account record! ");
		return 0;
	}
	/*...........*/
	rd=read(rfd,&myrecord,sizeof(myrecord));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(rfd, F_SETLK, &mylock);
	/*...........*/

	if(rd<=0){
		perror("Cannot read the file");
		return 0;
	}
	// Body.................
	switch(type){
	case 0: myrecord.new_s=next;
		break;
	case 1: myrecord.new_f=next;
		break;
	case 2: myrecord.new_c=next;
		break;
	default: return 0;
		break;
	}
	//update....
	offset=lseek(rfd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in Record File ");
		return 0;
	}

	/*Setting Lock*/
	mylock.l_type = F_WRLCK;
	mylock.l_start = 0*sizeof(struct record);
	lock = fcntl(rfd, F_SETLKW, &mylock);
	if(lock == -1)
	{
		perror("Error obtaining read lock on Account record!");
		return 0;
	}
	/*...........*/
	wt=write(rfd,&myrecord,sizeof(myrecord));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(rfd, F_SETLK, &mylock);
	/*...........*/
	if(wt<=0){
		perror("Cannot write into the file ");
		return 0;
	}

	close(rfd);
	return 1;
}

int get_all_record(int type){
	struct record myrecord;
	int rfd,rd,res, offset;
	rfd=open("./Record_File/record.txt",O_RDONLY);
	if(rfd==-1){
		perror("Cannot Open File ");
		return -1;
	}
	offset=lseek(rfd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in Record File ");
		return -1;
	}

	/*Setting Lock*/
	struct flock mylock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int rdlock = fcntl(rfd, F_SETLKW, &mylock);
	if(rdlock == -1)
	{
		perror("Error obtaining read lock on Account record!");
		return 0;
	}
	/*...........*/
	rd=read(rfd,&myrecord,sizeof(myrecord));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(rfd, F_SETLK, &mylock);
	/*...........*/
	if(rd<=0){
		perror("Cannot read the file ");
		return -1;
	}
	// Body.................
	switch(type){
	case 0: 
		res=myrecord.total_student;
		break;
	case 1: 
		res=myrecord.total_faculty;
		break;
	case 2: 
		res=myrecord.total_course;
		break;
	default: 
		return -1;
		break;
	}
	
	
	close(rfd);
	return res;
}

/*
int get_all_record(int type){
	struct record myrecord;
	int rfd,rd,res, offset;
	rfd=open("./Record_File/record.txt",O_RDONLY);
	if(rfd==-1){
		perror("Cannot Open File ");
		return -1;
	}
	offset=lseek(rfd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in Record File ");
		return -1;
	}


	struct flock mylock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int rdlock = fcntl(rfd, F_SETLKW, &mylock);
	if (rdlock == -1)
	{
		perror("Error obtaining read lock on Account record!");
		return 0;
	}

	rd=read(rfd,&myrecord,sizeof(myrecord));

	mylock.l_type = F_UNLCK;
	fcntl(rfd, F_SETLK, &mylock);

	if(rd<=0){
		perror("Cannot read the file ");
		return -1;
	}
	// Body.................
	switch(type){
	case 0: res=myrecord.total_student;
		break;
	case 1: res=myrecord.total_faculty;
		break;
	case 2: res=myrecord.total_course;
		break;
	default: return -1;
		break;
}

close(rfd);
return res;
}
*/
/*
int set_all_record(int type, int val){
	struct record myrecord;
	int rfd,rd,wt, offset;
	//open...
	rfd=open("./Record_File/record.txt",O_RDWR);
	if(rfd==-1){
		perror("Cannot Open File ");
		return 0;
	}
	//read...
	offset=lseek(rfd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in Record File ");
		return 0;
	}


	struct flock mylock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lock = fcntl(rfd, F_SETLKW, &mylock);
	if(lock == -1)
	{
		perror("Error obtaining read lock on Account record! ");
		return 0;
	}

	rd=read(rfd,&myrecord,sizeof(myrecord));
	wmsg2(cfd, 0, 1,"\nFaculty", myrecord.total_faculty);
		wmsg2(cfd, 0, 1,"\nStudent", myrecord.total_student);
			wmsg2(cfd, 0, 1,"\nCourse", myrecord.total_course);
	mylock.l_type = F_UNLCK;
	fcntl(rfd, F_SETLK, &mylock);

	if(rd<=0){
		perror("Cannot read the file");
		return 0;
	}
	
	// Body.................
	switch(type){
	case 0: myrecord.total_student=val;
		break;
	case 1: myrecord.total_faculty=val;
		break;
	case 2: myrecord.total_course=val;
		break;
	default: return 0;
		break;
	}
	wmsg2(cfd, 0, 1,"\nFaculty", myrecord.total_faculty);
		wmsg2(cfd, 0, 1,"\nStudent", myrecord.total_student);
			wmsg2(cfd, 0, 1,"\nCourse", myrecord.total_course);
	//update....
	offset=lseek(rfd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in Record File ");
		return 0;
	}


	mylock.l_type = F_WRLCK;
	mylock.l_start = 0*sizeof(struct record);
	lock = fcntl(rfd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining read lock on Account record!");
		return 0;
	}

	wt=write(rfd,&myrecord,sizeof(myrecord));

	wmsg2(cfd, 0, 1,"\nFaculty", myrecord.total_faculty);
		wmsg2(cfd, 0, 1,"\nStudent", myrecord.total_student);
			wmsg2(cfd, 0, 1,"\nCourse", myrecord.total_course);
	mylock.l_type = F_UNLCK;
	fcntl(rfd, F_SETLK, &mylock);

	if(wt<=0){
		perror("Cannot write into the file ");
		return 0;
	}

	close(rfd);
	return 1;
}
*/
int set_all_record(int type, int next){
	struct record myrecord;
	int rfd,rd,wt, offset;
	//open...
	rfd=open("./Record_File/record.txt",O_RDWR);
	if(rfd==-1){
		perror("Cannot Open File ");
		return 0;
	}
	//read...
	offset=lseek(rfd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in Record File ");
		return 0;
	}

	/*Setting Lock*/
	struct flock mylock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lock = fcntl(rfd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining read lock on Account record! ");
		return 0;
	}
	/*...........*/
	rd=read(rfd,&myrecord,sizeof(myrecord));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(rfd, F_SETLK, &mylock);
	/*...........*/

	if(rd<=0){
		perror("Cannot read the file");
		return 0;
	}
	// Body.................
	switch(type){
	case 0: myrecord.total_student=next;
		break;
	case 1: myrecord.total_faculty=next;
		break;
	case 2: myrecord.total_course=next;
		break;
	default: return 0;
		break;
	}
	//update....
	offset=lseek(rfd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in Record File ");
		return 0;
	}

	/*Setting Lock*/
	mylock.l_type = F_WRLCK;
	mylock.l_start = 0*sizeof(struct record);
	lock = fcntl(rfd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining read lock on Account record!");
		return 0;
	}
	/*...........*/
	wt=write(rfd,&myrecord,sizeof(myrecord));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(rfd, F_SETLK, &mylock);
	/*...........*/
	if(wt<=0){
		perror("Cannot write into the file ");
		return 0;
	}

	close(rfd);
	return 1;
}
