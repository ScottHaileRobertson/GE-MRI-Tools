function strct = ge_read_exam_header_rdb11(pfile_name,offset)


% Open the PFile
fid=fopen(pfile_name,'r','ieee-le');         %Little-Endian format
if (fid == -1)
	error(sprintf('Could not open %s file.',pfile_name));
end

% apply offset
fseek(fid,offset,'bof');

strct = struct('base_p_file',pfile_name);
strct = setfield(strct, 'firstaxtime', fread(fid,1,'double','ieee-le')); % Start time(secs) of first axial in exam
strct = setfield(strct, 'ex_series', fread(fid,1,'double','ieee-le')); % Series Keys for this Exam
strct = setfield(strct, 'ex_unseries', fread(fid,1,'double','ieee-le')); % Unstored Series Keys for this Exam
strct = setfield(strct, 'ex_toarchive', fread(fid,1,'double','ieee-le')); % Unarchived Series Keys for this Exam
strct = setfield(strct, 'ex_prosp', fread(fid,1,'double','ieee-le')); % Prospective/Scout Series Keys for this Exam
strct = setfield(strct, 'ex_models', fread(fid,1,'double','ieee-le')); % ThreeD Model Keys for Exam
strct = setfield(strct, 'zerocell', fread(fid,1,'float32','ieee-le')); % Cell number at theta
strct = setfield(strct, 'cellspace', fread(fid,1,'float32','ieee-le')); % Cell spacing
strct = setfield(strct, 'srctodet', fread(fid,1,'float32','ieee-le')); % Distance from source to detector
strct = setfield(strct, 'srctoiso', fread(fid,1,'float32','ieee-le')); % Distance from source to iso
strct = setfield(strct, 'ex_delta_cnt', fread(fid,1,'int32','ieee-le')); % Indicates number of updates to header
strct = setfield(strct, 'ex_complete', fread(fid,1,'int32','ieee-le')); % Exam Complete Flag
strct = setfield(strct, 'ex_seriesct', fread(fid,1,'int32','ieee-le')); % Last Series Number Used
strct = setfield(strct, 'ex_numarch', fread(fid,1,'int32','ieee-le')); % Number of Series Archived
strct = setfield(strct, 'ex_numseries', fread(fid,1,'int32','ieee-le')); % Number of Series Existing
strct = setfield(strct, 'ex_numunser', fread(fid,1,'int32','ieee-le')); % Number of Unstored Series
strct = setfield(strct, 'ex_toarchcnt', fread(fid,1,'int32','ieee-le')); % Number of Unarchived Series
strct = setfield(strct, 'ex_prospcnt', fread(fid,1,'int32','ieee-le')); % Number of Prospective/Scout Series
strct = setfield(strct, 'ex_modelnum', fread(fid,1,'int32','ieee-le')); % Last Model Number used
strct = setfield(strct, 'ex_modelcnt', fread(fid,1,'int32','ieee-le')); % Number of ThreeD Models
strct = setfield(strct, 'ex_checksum', fread(fid,1,'uint32','ieee-le')); % Exam Record Checksum
strct = setfield(strct, 'numcells', fread(fid,1,'int32','ieee-le')); % Number of cells in det
strct = setfield(strct, 'magstrength', fread(fid,1,'int32','ieee-le')); % Magnet strength (in gauss)
strct = setfield(strct, 'patweight', fread(fid,1,'int32','ieee-le')); % Patient Weight
strct = setfield(strct, 'ex_datetime', fread(fid,1,'int32','ieee-le')); % Exam date/time stamp
strct = setfield(strct, 'ex_lastmod', fread(fid,1,'int32','ieee-le')); % Date/Time of Last Change
strct = setfield(strct, 'ex_no', fread(fid,1,'uint16','ieee-le')); % Exam Number
strct = setfield(strct, 'ex_uniq', fread(fid,1,'int16','ieee-le')); % The Make-Unique Flag
strct = setfield(strct, 'detect', fread(fid,1,'int16','ieee-le')); % Detector Type
strct = setfield(strct, 'tubetyp', fread(fid,1,'int16','ieee-le')); % Tube type
strct = setfield(strct, 'dastyp', fread(fid,1,'int16','ieee-le')); % DAS type
strct = setfield(strct, 'num_dcnk', fread(fid,1,'int16','ieee-le')); % Number of Decon Kernals
strct = setfield(strct, 'dcn_len', fread(fid,1,'int16','ieee-le')); % Number of elements in a Decon Kernal
strct = setfield(strct, 'dcn_density', fread(fid,1,'int16','ieee-le')); % Decon Kernal density
strct = setfield(strct, 'dcn_stepsize', fread(fid,1,'int16','ieee-le')); % Decon Kernal stepsize
strct = setfield(strct, 'dcn_shiftcnt', fread(fid,1,'int16','ieee-le')); % Decon Kernal Shift Count
strct = setfield(strct, 'patage', fread(fid,1,'int16','ieee-le')); % Patient Age (years, months or days)
strct = setfield(strct, 'patian', fread(fid,1,'int16','ieee-le')); % Patient Age Notation
strct = setfield(strct, 'patsex', fread(fid,1,'int16','ieee-le')); % Patient Sex
strct = setfield(strct, 'ex_format', fread(fid,1,'int16','ieee-le')); % Exam Format
strct = setfield(strct, 'trauma', fread(fid,1,'int16','ieee-le')); % Trauma Flag
strct = setfield(strct, 'protocolflag', fread(fid,1,'int16','ieee-le')); % Non-Zero indicates Protocol Exam
strct = setfield(strct, 'study_status', fread(fid,1,'int16','ieee-le')); % indicates if study has complete info(DICOM/genesis)
strct = setfield(strct, 'padding', fread(fid,3,'int16','ieee-le'));
strct = setfield(strct, 'hist', char(fread(fid,61,'char','ieee-le'))); % Patient History
strct = setfield(strct, 'reqnum', char(fread(fid,13,'char','ieee-le'))); % Requisition Number
strct = setfield(strct, 'refphy', char(fread(fid,33,'char','ieee-le'))); % Referring Physician
strct = setfield(strct, 'diagrad', char(fread(fid,33,'char','ieee-le'))); % Diagnostician/Radiologist
strct = setfield(strct, 'op', char(fread(fid,4,'char','ieee-le'))); % Operator
strct = setfield(strct, 'ex_desc', char(fread(fid,65,'char','ieee-le'))); % Exam Description
strct = setfield(strct, 'ex_typ', char(fread(fid,3,'char','ieee-le'))); % Exam Type
strct = setfield(strct, 'ex_sysid', char(fread(fid,9,'char','ieee-le'))); % Creator Suite and Host
strct = setfield(strct, 'ex_alloc_key', char(fread(fid,13,'char','ieee-le'))); % Process that allocated this record
strct = setfield(strct, 'ex_diskid', char(fread(fid,1,'char','ieee-le'))); % Disk ID for this Exam
strct = setfield(strct, 'hospname', char(fread(fid,33,'char','ieee-le'))); % Hospital Name
strct = setfield(strct, 'patid', char(fread(fid,13,'char','ieee-le'))); % Patient ID for this Exam
strct = setfield(strct, 'patname', char(fread(fid,25,'char','ieee-le'))); % Patient Name
strct = setfield(strct, 'ex_suid', char(fread(fid,4,'char','ieee-le'))); % Suite ID for this Exam
strct = setfield(strct, 'ex_verscre', char(fread(fid,2,'char','ieee-le'))); % Genesis Version - Created
strct = setfield(strct, 'ex_verscur', char(fread(fid,2,'char','ieee-le'))); % Genesis Version - Now
strct = setfield(strct, 'uniq_sys_id', char(fread(fid,16,'char','ieee-le'))); % Unique System ID
strct = setfield(strct, 'service_id', char(fread(fid,16,'char','ieee-le'))); % Unique Service ID
strct = setfield(strct, 'mobile_loc', char(fread(fid,4,'char','ieee-le'))); % Mobile Location Number
strct = setfield(strct, 'study_uid', char(fread(fid,32,'char','ieee-le'))); % Study Entity Unique ID
strct = setfield(strct, 'refsopcuid', char(fread(fid,32,'char','ieee-le'))); % Ref SOP Class UID 
strct = setfield(strct, 'refsopiuid', char(fread(fid,32,'char','ieee-le'))); % Ref SOP Instance UID 
%                                                   /* Part of Ref Study Seq */
strct = setfield(strct, 'patnameff', char(fread(fid,65,'char','ieee-le'))); % FF Patient Name 
strct = setfield(strct, 'patidff', char(fread(fid,65,'char','ieee-le'))); % FF Patient ID 
strct = setfield(strct, 'reqnumff', char(fread(fid,17,'char','ieee-le'))); % FF Requisition No 
strct = setfield(strct, 'dateofbirth', char(fread(fid,9,'char','ieee-le'))); % Date of Birth 
strct = setfield(strct, 'mwlstudyuid', char(fread(fid,32,'char','ieee-le'))); % Genesis Exam UID 
strct = setfield(strct, 'mwlstudyid', char(fread(fid,16,'char','ieee-le'))); % Genesis Exam No 
strct = setfield(strct, 'ex_padding', char(fread(fid,222,'char','ieee-le'))); % Spare Space
%                                                   /* It doesn't affect the offsets on IRIX */
fclose(fid);
