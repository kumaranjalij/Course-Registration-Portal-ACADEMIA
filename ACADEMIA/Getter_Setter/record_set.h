int get_next_record(int type){
	struct record my_record;
	int record_fd,rBytes,retVal, offset;
	record_fd=open("./Record_File/record.txt",O_RDONLY);
	if(record_fd==-1){
	perror("Cannot Open File");
	return -1;
	}
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return -1;
	}

	/*Setting Lock*/
	struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on Account record!");
	return 0;
	}
	/*...........*/
	rBytes=read(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/
	if(rBytes<=0){
	perror("Cannot read the file");
	return -1;
	}
	// Body.................
	switch(type){
	case 0: retVal=my_record.new_s;
		break;
	case 1: retVal=my_record.new_f;
		break;
	case 2: retVal=my_record.new_c;
		break;
	default: return -1;
		break;
	}

	close(record_fd);
	return retVal;
}

int set_next_record(int type, int value){
	struct record my_record;
	int record_fd,rBytes,wBytes, offset;
	//open...
	record_fd=open("./Record_File/record.txt",O_RDWR);
	if(record_fd==-1){
	perror("Cannot Open File");
	return 0;
	}
	//read...
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return 0;
	}

	/*Setting Lock*/
	struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on Account record!");
	return 0;
	}
	/*...........*/
	rBytes=read(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/

	if(rBytes<=0){
	perror("Cannot read the file");
	return 0;
	}
	// Body.................
	switch(type){
	case 0: my_record.new_s=value;
		break;
	case 1: my_record.new_f=value;
		break;
	case 2: my_record.new_c=value;
		break;
	default: return 0;
		break;
	}
	//update....
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return 0;
	}

	/*Setting Lock*/
	lock.l_type = F_WRLCK;
	lock.l_start = 0*sizeof(struct record);
	lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on record!");
	return 0;
	}
	/*...........*/
	wBytes=write(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/
	if(wBytes<=0){
	perror("Cannot write into the file");
	return 0;
	}

	close(record_fd);
	return 1;
}

int get_all_record(int type){
	struct record my_record;
	int record_fd,rBytes,retVal, offset;
	record_fd=open("./Record_File/record.txt",O_RDONLY);
	if(record_fd==-1){
	perror("Cannot Open File");
	return -1;
	}
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return -1;
	}

	/*Setting Lock*/
	struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on Account record!");
	return 0;
	}
	/*...........*/
	rBytes=read(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/
	if(rBytes<=0){
	perror("Cannot read the file");
	return -1;
	}
	// Body.................
	switch(type){
	case 0: retVal=my_record.total_student;
		break;
	case 1: retVal=my_record.total_faculty;
		break;
	case 2: retVal=my_record.total_course;
		break;
	default: return -1;
		break;
	}

	close(record_fd);
	return retVal;
}

int set_all_record(int type, int value){
	struct record my_record;
	int record_fd,rBytes,wBytes, offset;
	//open...
	record_fd=open("./Record_File/record.txt",O_RDWR);
	if(record_fd==-1){
	perror("Cannot Open File");
	return 0;
	}
	//read...
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return 0;
	}

	/*Setting Lock*/
	struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on Account record!");
	return 0;
	}
	/*...........*/
	rBytes=read(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/

	if(rBytes<=0){
	perror("Cannot read the file");
	return 0;
	}
	// Body.................
	switch(type){
	case 0: my_record.total_student=value;
		break;
	case 1: my_record.total_faculty=value;
		break;
	case 2: my_record.total_course=value;
		break;
	default: return 0;
		break;
	}
	//update....
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return 0;
	}

	/*Setting Lock*/
	lock.l_type = F_WRLCK;
	lock.l_start = 0*sizeof(struct record);
	lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on record!");
	return 0;
	}
	/*...........*/
	wBytes=write(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/
	if(wBytes<=0){
	perror("Cannot write into the file");
	return 0;
	}

	close(record_fd);
	return 1;
}
