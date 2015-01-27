#!/usr/bin/perl -w
use strict;
use warnings;

# Get revision number from first user input
my ($revision_number_prefix) = @ARGV;

print "Making Pfile parser for rdbm rev $revision_number_prefix\n";

#Write matlab for rdb_header_rec
my $c_def_file = 'rdbm.h';
my $rdb_header_rec_start    = '.*typedef\s*struct\s*_RDB_HEADER_REC.*';
my $rdb_header_rec_end      = '.*}\s*RDB_HEADER_REC.*';
my $rdb_header_rec_function = "rdb_$revision_number_prefix";
&writeMatlabParserFunc($c_def_file, $rdb_header_rec_function, $rdb_header_rec_start, $rdb_header_rec_end);

#Write matlab for exam header
$c_def_file = 'imagedb.h';
my $exam_header_start    = '.*typedef\s*struct\s*_EXAMDATATYPE.*';
my $exam_header_end      = '.*}\s*EXAMDATATYPE.*';
my $exam_header_function = "exam_$revision_number_prefix";
&writeMatlabParserFunc($c_def_file, $exam_header_function, $exam_header_start, $exam_header_end);

#Write matlab for series header
my $series_header_start    = '.*typedef\s*struct\s*_\s*SERIESDATATYPE.*';
my $series_header_end      = '.*}\s*SERIESDATATYPE.*';
my $series_header_function = "series_$revision_number_prefix";
&writeMatlabParserFunc($c_def_file, $series_header_function, $series_header_start, $series_header_end);

#Write matlab for series header
my $image_header_start    = '.*typedef\s*struct\s*_MRIMAGEDATATYPE.*';
my $image_header_end      = '.*}\s*MRIMAGEDATATYPE.*';
my $image_header_function = "image_$revision_number_prefix";
&writeMatlabParserFunc($c_def_file, $image_header_function, $image_header_start, $image_header_end);
print "DONE!\n";

sub writeMatlabParserFunc{
my ($c_def_file, $matlab_function, $start_text, $end_text) = @_;

my $struct_base = "strct";
my %type_conversions = (	"int" => "int32",
				"float" => "float32",
				"long" => "int32",
				"unsigned long" => "uint32",
				"short" => "int16",
				"short int" => "int16",
				"unsigned short" => "uint16",
				"double" => "double",
				"char" => "char",
				"unsigned long int" => "uint32",
				"unsigned short int" => "uint16",
				"RDB_MULTI_RCV_TYPE" => "int32", #note, this should actaully be two shorts, but this lets us keep reading correctly
				"ATOMIC" => "int32",
				"BLOCK" => "char",
				"RASPOINT" => "float32",
				"DIMXYTYPE" => "float32",
				"PIXSIZETYPE" => "float32",
				"char*" => "int32",
				"IMATRIXTYPE" => "int16",
				"VARTYPE" => "double"); 

my $looking_in_right_place = 0; 
my $still_commenting = 0;

open (WRITEFILE, ">" . "$matlab_function" . ".m") or die $!;

print WRITEFILE "function $struct_base = $matlab_function(pfile_name,offset)\n\n";
print WRITEFILE "\n% Open the PFile\n";
print WRITEFILE "fid=fopen(pfile_name,\'r\',\'ieee-le\');         %Little-Endian format\n";
print WRITEFILE "if (fid == -1)\n";
print WRITEFILE "\terror(sprintf(\'Could not open %s file.\',pfile_name));\n";
print WRITEFILE "end\n\n";
print WRITEFILE "% apply offset\n";
print WRITEFILE "fseek(fid,offset,\'bof\');\n\n";
print WRITEFILE "$struct_base = struct(\'base_p_file\',pfile_name);\n";

open (READFILE, "<" . $c_def_file) or die $!;
while(my $line = <READFILE>){
	#Only read data structure between definition and end of definition

	if($line =~ m/$start_text/){
		#Finds the start of the data structure
		$looking_in_right_place = 1;
		next;
	}elsif($line =~ m/$end_text/){
		#Finds the end of the data structure
		$looking_in_right_place = 0;
		last; #Break out of while loop
	}elsif($looking_in_right_place == 1){
		# Now we are in the correct data type, so read every line carefully
		
		if($line =~ m/^\s*{\s*$/){
			#Ignore extra curly brace at top if necessary
			next;
		}
		
		if($line =~ m/^\s*#\s*define.*/){
			#ignore any define lines... not sure what these even do
			next;
		}
		
		if(! ($line =~ m/\S/)){
			#Ignore empty Lines
			print WRITEFILE "\n";
			next;
		}else{
			#print "\nLINE:$line";
			my ($pre_comment, $is_single_line, $c_type, $variable, $number, $post_comment) = &parseCLine($line, $still_commenting);
			
			#Check if we are in the middle of a multiline comment
			if($still_commenting){
				#just print comments
				print WRITEFILE "% $line";
				
				#Look for the end of the comment
				if(defined($is_single_line) & $is_single_line){
					$still_commenting = 0;
				}	
			}else{
				#Check if line is a comment
				if(defined($pre_comment)){
					#Check if its a one line or multiline comment
					if(defined($is_single_line) & $is_single_line){
						#its a one line comment
						$still_commenting = 0;
					}else{
						#Its a multiline comment
						$still_commenting = 1;
					}
					print WRITEFILE "% $line";
				}else{
					#Its not a comment, so its a line that needs to be translated
					#translate the data type
					#lookup matlab type
					if(defined($type_conversions{$c_type})){
						my $matlab_type = $type_conversions{$c_type};

						if(defined($matlab_type) & ("char" eq $matlab_type)){
							print WRITEFILE "$struct_base = setfield($struct_base, \'$variable\', char(fread(fid,$number,\'char\',\'ieee-le\')));";
						}else{
							print WRITEFILE "$struct_base = setfield($struct_base, \'$variable\', fread(fid,$number,\'$matlab_type\',\'ieee-le\'));";							
						}
							
						if(defined($post_comment)){
							print WRITEFILE " % $post_comment";
							#Handle multi line post comments
							if(defined($is_single_line) & $is_single_line){
								$still_commenting = 0;
							}else{
								$still_commenting = 1;
							}
						}
						print WRITEFILE "\n";		
					}else{
						print WRITEFILE "NO CONVERSION FOR $c_type LINE:$line\n";
					}
				}	
			}
			
		}
	}
}
close(READFILE);
print WRITEFILE "fclose(fid);\n";

close(WRITEFILE);
}

#
# This subroutine will parse out a line from a datastructure.
#
sub parseCLine{
	my ($line, $comment_line) = @_;
	my $pre_comment = undef;
	my $is_single_line = undef;
	my $types = undef;
	my $variable = undef;
	my $number = 1;
	my $post_comment = undef;
	if(!defined($comment_line)){
		$comment_line = 0;
	}
	
	my $c_types = "unsigned\\s|int\\s|short\\s|long\\s|float\\s|char\\s|RDB_MULTI_RCV_TYPE\\s|ATOMIC\\s|BLOCK\\s|double\\s|RASPOINT\\s|DIMXYTYPE\\s|PIXSIZETYPE\\s|char\\*\\s|IMATRIXTYPE\\s|VARTYPE\\s|"; 
	
	#Check if its a comment
	my $is_comment = ($line =~ m/^\s*\/\*(.*)/);
	if($is_comment | $comment_line){
		if($is_comment){
			$pre_comment = $1;
		}else{
			$pre_comment = $line;
		}
		#Check if its a single or multiline comment
		$is_single_line = ($pre_comment =~ m/\s*(.*)\s*\*\/\s*/);
		if($is_single_line){
			$pre_comment = $1;
		}
	}else{
		#Its not just a comment
		$line =~ m/\s*(($c_types|\s)*)(.*?)\s*;\s*(\/\*(.*)?\s*)?/;
		$types = $1;
		#2 -> Junk types (DO NOT USE)
		$variable = $3;
		
		if(defined($5)){
			$post_comment = $5;
		}
		if(defined($3)){
			#Check if there is a number of the same type
			my $mult_num = ($variable =~ m/\s*(.*?)\s*\[\s*(\d+)\s*\]\s*/);
			if($mult_num){
				$variable = $1;
				$number = $2;
			}
		}
		if(defined($post_comment)){
			#Check if its a single or multiline comment
			$is_single_line = ($post_comment =~ m/\s*(.*)\s*\*\/\s*/);
			if($is_single_line){
				$post_comment = $1;
			}
		}
	}
	
	if(defined($types)){		
		#Convert type into a neater format (one space between types)
		my @type_array = split(/\s+/,$types);
		$types = "";
		foreach my $next (@type_array){
			if(defined($next)){
				$types = "$types" . "$next ";
			}
		}
		#Remove trailing whitespace
		$types =~ /\s*(.*)\s+/;
		$types = $1;
		
	}
	
	if(defined($variable)){
		$variable =~ m/\s*(\S*)\s*/;
		$variable = $1;
	}
	
	return ($pre_comment, $is_single_line, $types, $variable, $number, $post_comment);
}
