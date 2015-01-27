function strct = ge_read_rdb_header_rec_rdb11(pfile_name,offset)


% Open the PFile
fid=fopen(pfile_name,'r','ieee-le');         %Little-Endian format
if (fid == -1)
	error(sprintf('Could not open %s file.',pfile_name));
end

% apply offset
fseek(fid,offset,'bof');

strct = struct('base_p_file',pfile_name);
strct = setfield(strct, 'rdb_hdr_rdbm_rev', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_run_int', fread(fid,1,'int32','ieee-le')); % Rdy pkt Run Number 
strct = setfield(strct, 'rdb_hdr_scan_seq', fread(fid,1,'int16','ieee-le')); % Rdy pkt Sequence Number 
strct = setfield(strct, 'rdb_hdr_run_char', char(fread(fid,6,'char','ieee-le'))); % Rdy pkt Run no in char 
strct = setfield(strct, 'rdb_hdr_scan_date', char(fread(fid,10,'char','ieee-le'))); % 
strct = setfield(strct, 'rdb_hdr_scan_time', char(fread(fid,8,'char','ieee-le'))); % 
strct = setfield(strct, 'rdb_hdr_logo', char(fread(fid,10,'char','ieee-le'))); % rdbm  used to verify file 

strct = setfield(strct, 'rdb_hdr_file_contents', fread(fid,1,'int16','ieee-le')); % Data type 0=emp 1=nrec 2=rw 	0, 1, 2 
strct = setfield(strct, 'rdb_hdr_lock_mode', fread(fid,1,'int16','ieee-le')); % unused 
strct = setfield(strct, 'rdb_hdr_dacq_ctrl', fread(fid,1,'int16','ieee-le')); % rhdacqctrl bit mask		15 bits 
strct = setfield(strct, 'rdb_hdr_recon_ctrl', fread(fid,1,'int16','ieee-le')); % rhrcctrl bit mask 		15 bits 
strct = setfield(strct, 'rdb_hdr_exec_ctrl', fread(fid,1,'int16','ieee-le')); % rhexecctrl bit mask 		15 bits 
strct = setfield(strct, 'rdb_hdr_scan_type', fread(fid,1,'int16','ieee-le')); % bit mask 			15 bits 
strct = setfield(strct, 'rdb_hdr_data_collect_type', fread(fid,1,'int16','ieee-le')); % rhtype  bit mask		15 bits 
strct = setfield(strct, 'rdb_hdr_data_format', fread(fid,1,'int16','ieee-le')); % rhformat  bit mask 		15 bits 
strct = setfield(strct, 'rdb_hdr_recon', fread(fid,1,'int16','ieee-le')); % rhrecon proc-a-son recon	0 - 100 
strct = setfield(strct, 'rdb_hdr_datacq', fread(fid,1,'int16','ieee-le')); % rhdatacq proc-a-son dacq 

strct = setfield(strct, 'rdb_hdr_npasses', fread(fid,1,'int16','ieee-le')); % rhnpasses  passes for a scan  0 - 256 
strct = setfield(strct, 'rdb_hdr_npomp', fread(fid,1,'int16','ieee-le')); % rhnpomp  pomp group slices  	1,2 
strct = setfield(strct, 'rdb_hdr_nslices', fread(fid,1,'int16','ieee-le')); % rhnslices  slices in a pass	0 - 256 
strct = setfield(strct, 'rdb_hdr_nechoes', fread(fid,1,'int16','ieee-le')); % rhnecho  echoes of a slice	1 - 32 
strct = setfield(strct, 'rdb_hdr_navs', fread(fid,1,'int16','ieee-le')); % rhnavs  num of excitiations  	1 - 32727 
strct = setfield(strct, 'rdb_hdr_nframes', fread(fid,1,'int16','ieee-le')); % rhnframes  yres		0 - 1024 
strct = setfield(strct, 'rdb_hdr_baseline_views', fread(fid,1,'int16','ieee-le')); % rhbline  baselines		0 - 1028 
strct = setfield(strct, 'rdb_hdr_hnover', fread(fid,1,'int16','ieee-le')); % rhhnover  overscans		0 - 1024 
strct = setfield(strct, 'rdb_hdr_frame_size', fread(fid,1,'uint16','ieee-le')); % rhfrsize  xres 		0 - 32768 
strct = setfield(strct, 'rdb_hdr_point_size', fread(fid,1,'int16','ieee-le')); % rhptsize			2 - 4 

strct = setfield(strct, 'rdb_hdr_vquant', fread(fid,1,'int16','ieee-le')); % rhvquant 3d volumes		1 

strct = setfield(strct, 'rdb_hdr_cheart', fread(fid,1,'int16','ieee-le')); % RX Cine heart phases 		1 - 32 
strct = setfield(strct, 'rdb_hdr_ctr', fread(fid,1,'float32','ieee-le')); % RX Cine TR in sec		0 - 3.40282e38
strct = setfield(strct, 'rdb_hdr_ctrr', fread(fid,1,'float32','ieee-le')); % RX Cine RR in sec 		0 - 30.0 

strct = setfield(strct, 'rdb_hdr_initpass', fread(fid,1,'int16','ieee-le')); % rhinitpass allocate passes    0 - 32767 
strct = setfield(strct, 'rdb_hdr_incrpass', fread(fid,1,'int16','ieee-le')); % rhincrpass tps autopauses	0 - 32767 

strct = setfield(strct, 'rdb_hdr_method_ctrl', fread(fid,1,'int16','ieee-le')); % rhmethod  0=recon, 1=psd	0, 1 
strct = setfield(strct, 'rdb_hdr_da_xres', fread(fid,1,'uint16','ieee-le')); % rhdaxres 			0 - 32768 
strct = setfield(strct, 'rdb_hdr_da_yres', fread(fid,1,'int16','ieee-le')); % rhdayres 			0 - 2049 
strct = setfield(strct, 'rdb_hdr_rc_xres', fread(fid,1,'int16','ieee-le')); % rhrcxres 			0 - 1024 
strct = setfield(strct, 'rdb_hdr_rc_yres', fread(fid,1,'int16','ieee-le')); % rhrcyres 			0 - 1024 
strct = setfield(strct, 'rdb_hdr_im_size', fread(fid,1,'int16','ieee-le')); % rhimsize 			0 - 512 
strct = setfield(strct, 'rdb_hdr_rc_zres', fread(fid,1,'int32','ieee-le')); % power of 2 > rhnslices	0 - 128 

%    /*
%       These variables are changed to unsigned int to support greater than 2GB of BAM.
%       Throughout RECON the same change has been made by using the typedef BAM_size 
%       defined in bam.h
%       */
strct = setfield(strct, 'rdb_hdr_raw_pass_size', fread(fid,1,'uint32','ieee-le')); % rhrawsize 			0 - 2147483647
strct = setfield(strct, 'rdb_hdr_sspsave', fread(fid,1,'uint32','ieee-le')); % rhsspsave 			0 - 2147483647
strct = setfield(strct, 'rdb_hdr_udasave', fread(fid,1,'uint32','ieee-le')); % rhudasave 			0 - 2147483647

strct = setfield(strct, 'rdb_hdr_fermi_radius', fread(fid,1,'float32','ieee-le')); % rhfermr fermi radius		0 - 3.40282e38
strct = setfield(strct, 'rdb_hdr_fermi_width', fread(fid,1,'float32','ieee-le')); % rhfermw fermi width		0 - 3.40282e38
strct = setfield(strct, 'rdb_hdr_fermi_ecc', fread(fid,1,'float32','ieee-le')); % rhferme fermi excentiricty	0 - 3.40282e38
strct = setfield(strct, 'rdb_hdr_clip_min', fread(fid,1,'float32','ieee-le')); % rhclipmin 4x IP limit		+-16383 
strct = setfield(strct, 'rdb_hdr_clip_max', fread(fid,1,'float32','ieee-le')); % rhclipmax 4x IP limit		+-16383 
strct = setfield(strct, 'rdb_hdr_default_offset', fread(fid,1,'float32','ieee-le')); % rhdoffset default offset = 0	+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_xoff', fread(fid,1,'float32','ieee-le')); % rhxoff scroll img in x 	+-256 
strct = setfield(strct, 'rdb_hdr_yoff', fread(fid,1,'float32','ieee-le')); % rhyoff scroll img in y	+-256 
strct = setfield(strct, 'rdb_hdr_nwin', fread(fid,1,'float32','ieee-le')); % rhnwin hecho window width	0 - 256 
strct = setfield(strct, 'rdb_hdr_ntran', fread(fid,1,'float32','ieee-le')); % rhntran hecho trans width	0 - 256 
strct = setfield(strct, 'rdb_hdr_scalei', fread(fid,1,'float32','ieee-le')); % PS rhscalei			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_scaleq', fread(fid,1,'float32','ieee-le')); % PS rhscaleq  def = 0		+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_rotation', fread(fid,1,'int16','ieee-le')); % RX 0 90 180 270 deg		0 - 3 
strct = setfield(strct, 'rdb_hdr_transpose', fread(fid,1,'int16','ieee-le')); % RX 0, 1 n / y transpose 	0 - 1
strct = setfield(strct, 'rdb_hdr_kissoff_views', fread(fid,1,'int16','ieee-le')); % rhblank zero image views	0 - 512 
strct = setfield(strct, 'rdb_hdr_slblank', fread(fid,1,'int16','ieee-le')); % rhslblank  slice blank 3d	0 - 128 
strct = setfield(strct, 'rdb_hdr_gradcoil', fread(fid,1,'int16','ieee-le')); % RX 0=off 1=Schnk 2=Rmr	0 - 2 
strct = setfield(strct, 'rdb_hdr_ddaover', fread(fid,1,'int16','ieee-le')); % rhddaover unused 

strct = setfield(strct, 'rdb_hdr_sarr', fread(fid,1,'int16','ieee-le')); % SARR bit mask 		15 bits 
strct = setfield(strct, 'rdb_hdr_fd_tr', fread(fid,1,'int16','ieee-le')); % SARR feeder timing info 
strct = setfield(strct, 'rdb_hdr_fd_te', fread(fid,1,'int16','ieee-le')); % SARR feeder timing info 
strct = setfield(strct, 'rdb_hdr_fd_ctrl', fread(fid,1,'int16','ieee-le')); % SARR control of feeder 
strct = setfield(strct, 'rdb_hdr_algor_num', fread(fid,1,'int16','ieee-le')); % SARR df decimation ratio 
strct = setfield(strct, 'rdb_hdr_fd_df_dec', fread(fid,1,'int16','ieee-le')); % SARR which feeder algor 

strct = setfield(strct, 'rdb_hdr_dab', fread(fid,4,'int32','ieee-le')); % rhdab0s rhdab0e st, stp rcv 	0 - 15 

strct = setfield(strct, 'rdb_hdr_user0', fread(fid,1,'float32','ieee-le')); % rhuser0 			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user1', fread(fid,1,'float32','ieee-le')); % rhuser1 			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user2', fread(fid,1,'float32','ieee-le')); % rhuser2 			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user3', fread(fid,1,'float32','ieee-le')); % rhuser3 			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user4', fread(fid,1,'float32','ieee-le')); % rhuser4 			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user5', fread(fid,1,'float32','ieee-le')); % rhuser5 			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user6', fread(fid,1,'float32','ieee-le')); % rhuser6 			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user7', fread(fid,1,'float32','ieee-le')); % rhuser7 			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user8', fread(fid,1,'float32','ieee-le')); % rhuser8 			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user9', fread(fid,1,'float32','ieee-le')); % rhuser9 			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user10', fread(fid,1,'float32','ieee-le')); % rhuser10			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user11', fread(fid,1,'float32','ieee-le')); % rhuser11			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user12', fread(fid,1,'float32','ieee-le')); % rhuser12			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user13', fread(fid,1,'float32','ieee-le')); % rhuser13			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user14', fread(fid,1,'float32','ieee-le')); % rhuser14			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user15', fread(fid,1,'float32','ieee-le')); % rhuser15			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user16', fread(fid,1,'float32','ieee-le')); % rhuser16			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user17', fread(fid,1,'float32','ieee-le')); % rhuser17			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user18', fread(fid,1,'float32','ieee-le')); % rhuser18			+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_user19', fread(fid,1,'float32','ieee-le')); % rhuser19			+-3.40282e38 

strct = setfield(strct, 'rdb_hdr_v_type', fread(fid,1,'int32','ieee-le')); % rhvtype  bit mask		31 bits 
strct = setfield(strct, 'rdb_hdr_v_coefxa', fread(fid,1,'float32','ieee-le')); % RX x flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefxb', fread(fid,1,'float32','ieee-le')); % RX x flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefxc', fread(fid,1,'float32','ieee-le')); % RX x flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefxd', fread(fid,1,'float32','ieee-le')); % RX x flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefya', fread(fid,1,'float32','ieee-le')); % RX y flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefyb', fread(fid,1,'float32','ieee-le')); % RX y flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefyc', fread(fid,1,'float32','ieee-le')); % RX y flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefyd', fread(fid,1,'float32','ieee-le')); % RX y flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefza', fread(fid,1,'float32','ieee-le')); % RX z flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefzb', fread(fid,1,'float32','ieee-le')); % RX z flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefzc', fread(fid,1,'float32','ieee-le')); % RX z flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_v_coefzd', fread(fid,1,'float32','ieee-le')); % RX z flow direction control	0 - 4 
strct = setfield(strct, 'rdb_hdr_vm_coef1', fread(fid,1,'float32','ieee-le')); % RX weight for mag image 1	0 - 1 
strct = setfield(strct, 'rdb_hdr_vm_coef2', fread(fid,1,'float32','ieee-le')); % RX weight for mag image 2	0 - 1 
strct = setfield(strct, 'rdb_hdr_vm_coef3', fread(fid,1,'float32','ieee-le')); % RX weight for mag image 3	0 - 1 
strct = setfield(strct, 'rdb_hdr_vm_coef4', fread(fid,1,'float32','ieee-le')); % RX weight for mag image 4	0 - 1 
strct = setfield(strct, 'rdb_hdr_v_venc', fread(fid,1,'float32','ieee-le')); % RX vel encodeing cm / sec	0.001 - 5000 

strct = setfield(strct, 'spectral_width', fread(fid,1,'float32','ieee-le')); % specwidth  filter width kHz	500 - 3355432 
strct = setfield(strct, 'csi_dims', fread(fid,1,'int16','ieee-le')); % spectro 
strct = setfield(strct, 'xcsi', fread(fid,1,'int16','ieee-le')); % rhspecrescsix  		2 - 64 
strct = setfield(strct, 'ycsi', fread(fid,1,'int16','ieee-le')); % rhspecrescsiy  		2 - 64 
strct = setfield(strct, 'zcsi', fread(fid,1,'int16','ieee-le')); % spectro 
strct = setfield(strct, 'roilenx', fread(fid,1,'float32','ieee-le')); % RX x csi volume dimension 
strct = setfield(strct, 'roileny', fread(fid,1,'float32','ieee-le')); % RX y csi volume dimension 
strct = setfield(strct, 'roilenz', fread(fid,1,'float32','ieee-le')); % RX z csi volume dimension 
strct = setfield(strct, 'roilocx', fread(fid,1,'float32','ieee-le')); % RX x csi volume center 
strct = setfield(strct, 'roilocy', fread(fid,1,'float32','ieee-le')); % RX y csi volume center 
strct = setfield(strct, 'roilocz', fread(fid,1,'float32','ieee-le')); % RX z csi volume center 
strct = setfield(strct, 'numdwell', fread(fid,1,'float32','ieee-le')); % specdwells			0 - 3.40282e38

strct = setfield(strct, 'rdb_hdr_ps_command', fread(fid,1,'int32','ieee-le')); % PS internal use only	
strct = setfield(strct, 'rdb_hdr_ps_mps_r1', fread(fid,1,'int32','ieee-le')); % PS MPS R1 setting  		1 - 7 
strct = setfield(strct, 'rdb_hdr_ps_mps_r2', fread(fid,1,'int32','ieee-le')); % PS MPS R2 setting		1 - 30 
strct = setfield(strct, 'rdb_hdr_ps_mps_tg', fread(fid,1,'int32','ieee-le')); % PS MPS Transmit gain setting	0 - 200
strct = setfield(strct, 'rdb_hdr_ps_mps_freq', fread(fid,1,'int32','ieee-le')); % PS MPS Center frequency hz	+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_ps_aps_r1', fread(fid,1,'int32','ieee-le')); % PS APS R1 setting		1 - 7 
strct = setfield(strct, 'rdb_hdr_ps_aps_r2', fread(fid,1,'int32','ieee-le')); % PS APS R2 setting		1 - 30 
strct = setfield(strct, 'rdb_hdr_ps_aps_tg', fread(fid,1,'int32','ieee-le')); % PS APS Transmit gain setting	0 - 200
strct = setfield(strct, 'rdb_hdr_ps_aps_freq', fread(fid,1,'int32','ieee-le')); % PS APS Center frequency hz	+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_ps_scalei', fread(fid,1,'float32','ieee-le')); % PS rational scaling 		+-3.40282e38 
strct = setfield(strct, 'rdb_hdr_ps_scaleq', fread(fid,1,'float32','ieee-le')); % PS unused 
strct = setfield(strct, 'rdb_hdr_ps_snr_warning', fread(fid,1,'int32','ieee-le')); % PS noise test 0=16 1=32 bits	0, 1 
strct = setfield(strct, 'rdb_hdr_ps_aps_or_mps', fread(fid,1,'int32','ieee-le')); % PS prescan order logic	0 - 5 
strct = setfield(strct, 'rdb_hdr_ps_mps_bitmap', fread(fid,1,'int32','ieee-le')); % PS bit mask			4 bits
strct = setfield(strct, 'rdb_hdr_ps_powerspec', char(fread(fid,256,'char','ieee-le'))); % PS                             
strct = setfield(strct, 'rdb_hdr_ps_filler1', fread(fid,1,'int32','ieee-le')); % PS filler 
strct = setfield(strct, 'rdb_hdr_ps_filler2', fread(fid,1,'int32','ieee-le')); % PS filler 
strct = setfield(strct, 'rdb_hdr_rec_noise_mean', fread(fid,16,'float32','ieee-le')); % PS mean noise each receiver   +-3.40282e38 
strct = setfield(strct, 'rdb_hdr_rec_noise_std', fread(fid,16,'float32','ieee-le')); % PS noise calc for muti rec  	+-3.40282e38 

strct = setfield(strct, 'halfecho', fread(fid,1,'int16','ieee-le')); % spectro full, half echo       0, 1 
%    /* 858 bytes */

%    /* New fields 02-19-92 */
strct = setfield(strct, 'rdb_hdr_im_size_y', fread(fid,1,'int16','ieee-le')); % rh???? 			0 - 512 
strct = setfield(strct, 'rdb_hdr_data_collect_type1', fread(fid,1,'int32','ieee-le')); % rh???? bit mask		31 bits 
strct = setfield(strct, 'rdb_hdr_freq_scale', fread(fid,1,'float32','ieee-le')); % rh???? freq k-space step      +-3.40282e38 
strct = setfield(strct, 'rdb_hdr_phase_scale', fread(fid,1,'float32','ieee-le')); % rh???? freq k-space step      +-3.40282e38 
%    /* 14 bytes */
strct = setfield(strct, 'rdb_hdr_ovl', fread(fid,1,'int16','ieee-le')); % rhovl - overlaps for MOTSA 

%    /* Phase Correction Control Param. */
strct = setfield(strct, 'rdb_hdr_pclin', fread(fid,1,'int16','ieee-le')); % Linear Corr. 0:off, 1:linear, 2:polynomial 
strct = setfield(strct, 'rdb_hdr_pclinnpts', fread(fid,1,'int16','ieee-le')); % fit number of points 
strct = setfield(strct, 'rdb_hdr_pclinorder', fread(fid,1,'int16','ieee-le')); % fit order 
strct = setfield(strct, 'rdb_hdr_pclinavg', fread(fid,1,'int16','ieee-le')); % linear phase corr avg 0:off, 1:on 
strct = setfield(strct, 'rdb_hdr_pccon', fread(fid,1,'int16','ieee-le')); % Const Corr. 0:off, 1:Ky spec., 2:polyfit(2/ilv), 3:polyfit(1/ilv) 
strct = setfield(strct, 'rdb_hdr_pcconnpts', fread(fid,1,'int16','ieee-le')); % fit number of points 
strct = setfield(strct, 'rdb_hdr_pcconorder', fread(fid,1,'int16','ieee-le')); % fit order 
strct = setfield(strct, 'rdb_hdr_pcextcorr', fread(fid,1,'int16','ieee-le')); % external correction file 0:don't use, 1: use 
strct = setfield(strct, 'rdb_hdr_pcgraph', fread(fid,1,'int16','ieee-le')); % Phase Correction coef. image 0:off, 1:linear & constant 
strct = setfield(strct, 'rdb_hdr_pcileave', fread(fid,1,'int16','ieee-le')); % Interleaves to use for correction: 0=all, 1=only first 
strct = setfield(strct, 'rdb_hdr_hdbestky', fread(fid,1,'int16','ieee-le')); % bestky view for fractional Ky scan 
strct = setfield(strct, 'rdb_hdr_pcctrl', fread(fid,1,'int16','ieee-le')); % phase correction research control 
strct = setfield(strct, 'rdb_hdr_pcthrespts', fread(fid,1,'int16','ieee-le')); % 2..512 adjacent points 
strct = setfield(strct, 'rdb_hdr_pcdiscbeg', fread(fid,1,'int16','ieee-le')); % 0..512 beginning point to discard 
strct = setfield(strct, 'rdb_hdr_pcdiscmid', fread(fid,1,'int16','ieee-le')); % 0..512 middle point to discard 
strct = setfield(strct, 'rdb_hdr_pcdiscend', fread(fid,1,'int16','ieee-le')); % 0..512 ending point to discard 
strct = setfield(strct, 'rdb_hdr_pcthrespct', fread(fid,1,'int16','ieee-le')); % Threshold percentage 
strct = setfield(strct, 'rdb_hdr_pcspacial', fread(fid,1,'int16','ieee-le')); % Spacial best ref scan index 0..512 
strct = setfield(strct, 'rdb_hdr_pctemporal', fread(fid,1,'int16','ieee-le')); % Temporal best ref scan index 0..512 
strct = setfield(strct, 'rdb_hdr_pcspare', fread(fid,1,'int16','ieee-le')); % spare for phase correction 
strct = setfield(strct, 'rdb_hdr_ileaves', fread(fid,1,'int16','ieee-le')); % Number of interleaves 
strct = setfield(strct, 'rdb_hdr_kydir', fread(fid,1,'int16','ieee-le')); % Ky traversal dircetion 0: top-down, 1:center out 
strct = setfield(strct, 'rdb_hdr_alt', fread(fid,1,'int16','ieee-le')); % Alt read sign 0=no, 1=odd/even, 2=pairs 
strct = setfield(strct, 'rdb_hdr_reps', fread(fid,1,'int16','ieee-le')); % Number of scan repetitions 
strct = setfield(strct, 'rdb_hdr_ref', fread(fid,1,'int16','ieee-le')); % Ref Scan 0: off 1: on 

strct = setfield(strct, 'rdb_hdr_pcconnorm', fread(fid,1,'float32','ieee-le')); % Constant S term normalization factor 
strct = setfield(strct, 'rdb_hdr_pcconfitwt', fread(fid,1,'float32','ieee-le')); % Constant polyfit weighting factor 
strct = setfield(strct, 'rdb_hdr_pclinnorm', fread(fid,1,'float32','ieee-le')); % Linear   S term normalization factor 
strct = setfield(strct, 'rdb_hdr_pclinfitwt', fread(fid,1,'float32','ieee-le')); % Linear   polyfit weighting factor 

strct = setfield(strct, 'rdb_hdr_pcbestky', fread(fid,1,'float32','ieee-le')); % Best Ky location 

%    /* VRG Filter param */
strct = setfield(strct, 'rdb_hdr_vrgf', fread(fid,1,'int32','ieee-le')); % control word for VRG filter 
strct = setfield(strct, 'rdb_hdr_vrgfxres', fread(fid,1,'int32','ieee-le')); % control word for VRGF final x resolution 


%    /* Bandpass Asymmetry  Correction Param. */
strct = setfield(strct, 'rdb_hdr_bp_corr', fread(fid,1,'int32','ieee-le')); % control word for bandpass asymmetry 
strct = setfield(strct, 'rdb_hdr_recv_freq_s', fread(fid,1,'float32','ieee-le')); % starting frequency (+62.5) 
strct = setfield(strct, 'rdb_hdr_recv_freq_e', fread(fid,1,'float32','ieee-le')); % ending   frequency (-62.5) 

strct = setfield(strct, 'rdb_hdr_hniter', fread(fid,1,'int32','ieee-le')); %  Selects the number of
%                                      iterations used in homodyne processing */

strct = setfield(strct, 'rdb_hdr_fast_rec', fread(fid,1,'int32','ieee-le')); %  Added for homodyne II, tells if
%                                           teh fast receiver is being used
%                                           and the lpf setting of teh fast
%                                           receiver, 0: fast receiver off,
%                                           1 - 5: lpf settings   */

strct = setfield(strct, 'rdb_hdr_refframes', fread(fid,1,'int32','ieee-le')); % total # of frames for ref scan 
strct = setfield(strct, 'rdb_hdr_refframep', fread(fid,1,'int32','ieee-le')); % # of frames per pass for a ref scan 
strct = setfield(strct, 'rdb_hdr_scnframe', fread(fid,1,'int32','ieee-le')); % total # of frames for a entire scan 
strct = setfield(strct, 'rdb_hdr_pasframe', fread(fid,1,'int32','ieee-le')); % # of frames per pass 

strct = setfield(strct, 'rdb_hdr_user_usage_tag', fread(fid,1,'uint32','ieee-le')); % for spectro 
strct = setfield(strct, 'rdb_hdr_user_fill_mapMSW', fread(fid,1,'uint32','ieee-le')); % for spectro 
strct = setfield(strct, 'rdb_hdr_user_fill_mapLSW', fread(fid,1,'uint32','ieee-le')); % for Spectro 

strct = setfield(strct, 'rdb_hdr_user20', fread(fid,1,'float32','ieee-le')); % all following usercv are for spectro 
strct = setfield(strct, 'rdb_hdr_user21', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user22', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user23', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user24', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user25', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user26', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user27', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user28', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user29', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user30', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user31', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user32', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user33', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user34', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user35', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user36', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user37', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user38', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user39', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user40', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user41', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user42', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user43', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user44', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user45', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user46', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user47', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_user48', fread(fid,1,'float32','ieee-le'));

strct = setfield(strct, 'rdb_hdr_pcfitorig', fread(fid,1,'int16','ieee-le')); % Adjust view indexes if set so bestky view = 0 
strct = setfield(strct, 'rdb_hdr_pcshotfirst', fread(fid,1,'int16','ieee-le')); % First view within an echo group used for fit  
strct = setfield(strct, 'rdb_hdr_pcshotlast', fread(fid,1,'int16','ieee-le')); % Last view within an echo group used for fit   
strct = setfield(strct, 'rdb_hdr_pcmultegrp', fread(fid,1,'int16','ieee-le')); % If = 1, force pts from other egrps to be used 
strct = setfield(strct, 'rdb_hdr_pclinfix', fread(fid,1,'int16','ieee-le')); % If = 2, force slope to be set to pclinslope   
%                                   /* If = 1, neg readout slope = pos readout slope */
strct = setfield(strct, 'rdb_hdr_pcconfix', fread(fid,1,'int16','ieee-le')); % If = 2, force slope to be set to pcconslope   
%                                   /* If = 1, neg readout slope = pos readout slope */
strct = setfield(strct, 'rdb_hdr_pclinslope', fread(fid,1,'float32','ieee-le')); % Value to set lin slope to if forced           
strct = setfield(strct, 'rdb_hdr_pcconslope', fread(fid,1,'float32','ieee-le')); % Value to set con slope to if forced           
strct = setfield(strct, 'rdb_hdr_pccoil', fread(fid,1,'int16','ieee-le')); % If 1,2,3,4, use that coil's results for all   

%    /* Variable View Sharing */
strct = setfield(strct, 'rdb_hdr_vvsmode', fread(fid,1,'int16','ieee-le')); % Variable view sharing mode 
strct = setfield(strct, 'rdb_hdr_vvsaimgs', fread(fid,1,'int16','ieee-le')); % number of original images 
strct = setfield(strct, 'rdb_hdr_vvstr', fread(fid,1,'int16','ieee-le')); % TR in microseconds 
strct = setfield(strct, 'rdb_hdr_vvsgender', fread(fid,1,'int16','ieee-le')); % gender: male or female 

%    /* 3D Slice ZIP */
strct = setfield(strct, 'rdb_hdr_zip_factor', fread(fid,1,'int16','ieee-le')); % Slice ZIP factor: 0=OFF, 2, or 4 

%    /* Maxwell Term Correction Coefficients */
strct = setfield(strct, 'rdb_hdr_maxcoef1a', fread(fid,1,'float32','ieee-le')); % Coefficient A for flow image 1 
strct = setfield(strct, 'rdb_hdr_maxcoef1b', fread(fid,1,'float32','ieee-le')); % Coefficient B for flow image 1 
strct = setfield(strct, 'rdb_hdr_maxcoef1c', fread(fid,1,'float32','ieee-le')); % Coefficient C for flow image 1 
strct = setfield(strct, 'rdb_hdr_maxcoef1d', fread(fid,1,'float32','ieee-le')); % Coefficient D for flow image 1 
strct = setfield(strct, 'rdb_hdr_maxcoef2a', fread(fid,1,'float32','ieee-le')); % Coefficient A for flow image 2 
strct = setfield(strct, 'rdb_hdr_maxcoef2b', fread(fid,1,'float32','ieee-le')); % Coefficient B for flow image 2 
strct = setfield(strct, 'rdb_hdr_maxcoef2c', fread(fid,1,'float32','ieee-le')); % Coefficient C for flow image 2 
strct = setfield(strct, 'rdb_hdr_maxcoef2d', fread(fid,1,'float32','ieee-le')); % Coefficient D for flow image 2 
strct = setfield(strct, 'rdb_hdr_maxcoef3a', fread(fid,1,'float32','ieee-le')); % Coefficient A for flow image 3 
strct = setfield(strct, 'rdb_hdr_maxcoef3b', fread(fid,1,'float32','ieee-le')); % Coefficient B for flow image 3 
strct = setfield(strct, 'rdb_hdr_maxcoef3c', fread(fid,1,'float32','ieee-le')); % Coefficient C for flow image 3 
strct = setfield(strct, 'rdb_hdr_maxcoef3d', fread(fid,1,'float32','ieee-le')); % Coefficient D for flow image 3 

strct = setfield(strct, 'rdb_hdr_ut_ctrl', fread(fid,1,'int32','ieee-le')); % System utility control variable 
strct = setfield(strct, 'rdb_hdr_dp_type', fread(fid,1,'int16','ieee-le')); % EPI II diffusion control cv 

strct = setfield(strct, 'rdb_hdr_arw', fread(fid,1,'int16','ieee-le')); % Arrhythmia rejection window(percentage:1-100)

strct = setfield(strct, 'rdb_hdr_vps', fread(fid,1,'int16','ieee-le')); % View Per Segment for FastCine 

strct = setfield(strct, 'rdb_hdr_mcReconEnable', fread(fid,1,'int16','ieee-le')); % N-Coil recon map 
strct = setfield(strct, 'rdb_hdr_fov', fread(fid,1,'float32','ieee-le')); % Auto-NCoil 

strct = setfield(strct, 'rdb_hdr_te', fread(fid,1,'int32','ieee-le')); % TE for first echo                     
strct = setfield(strct, 'rdb_hdr_te2', fread(fid,1,'int32','ieee-le')); % TE for second and later echoes        
strct = setfield(strct, 'rdb_hdr_dfmrbw', fread(fid,1,'float32','ieee-le')); % BW for navigator frames               
strct = setfield(strct, 'rdb_hdr_dfmctrl', fread(fid,1,'int32','ieee-le')); % Control flag for dfm (0=off, other=on)
strct = setfield(strct, 'rdb_hdr_raw_nex', fread(fid,1,'int32','ieee-le')); % Uncombined NEX at start of recon      
strct = setfield(strct, 'rdb_hdr_navs_per_pass', fread(fid,1,'int32','ieee-le')); % Max. navigator frames in a pass       
strct = setfield(strct, 'rdb_hdr_dfmxres', fread(fid,1,'int32','ieee-le')); % xres of navigator frames              
strct = setfield(strct, 'rdb_hdr_dfmptsize', fread(fid,1,'int32','ieee-le')); % point size of navigator frames        
strct = setfield(strct, 'rdb_hdr_navs_per_view', fread(fid,1,'int32','ieee-le')); % Num. navigators per frame (tag table) 
strct = setfield(strct, 'rdb_hdr_dfmdebug', fread(fid,1,'int32','ieee-le')); % control flag for dfm debug            
strct = setfield(strct, 'rdb_hdr_dfmthreshold', fread(fid,1,'float32','ieee-le')); % threshold for navigator correction    

%    /* Section added to support gridding */
strct = setfield(strct, 'rdb_hdr_grid_control', fread(fid,1,'int16','ieee-le')); % bit settings controlling gridding 
strct = setfield(strct, 'rdb_hdr_b0map', fread(fid,1,'int16','ieee-le')); % B0 map enable and map size 
strct = setfield(strct, 'rdb_hdr_grid_tediff', fread(fid,1,'int16','ieee-le')); % TE difference between b0 map arms 
strct = setfield(strct, 'rdb_hdr_grid_motion_comp', fread(fid,1,'int16','ieee-le')); % flag to apply motion compensation 
strct = setfield(strct, 'rdb_hdr_grid_radius_a', fread(fid,1,'float32','ieee-le')); % variable density transition 
strct = setfield(strct, 'rdb_hdr_grid_radius_b', fread(fid,1,'float32','ieee-le')); % variable density transition 
strct = setfield(strct, 'rdb_hdr_grid_max_gradient', fread(fid,1,'float32','ieee-le')); % Max gradient amplitude 
strct = setfield(strct, 'rdb_hdr_grid_max_slew', fread(fid,1,'float32','ieee-le')); % Max slew rate 
strct = setfield(strct, 'rdb_hdr_grid_scan_fov', fread(fid,1,'float32','ieee-le')); % Rx scan field of view 
strct = setfield(strct, 'rdb_hdr_grid_a2d_time', fread(fid,1,'float32','ieee-le')); % A to D sample time microsecs 
strct = setfield(strct, 'rdb_hdr_grid_density_factor', fread(fid,1,'float32','ieee-le')); % change factor for variable density 
strct = setfield(strct, 'rdb_hdr_grid_display_fov', fread(fid,1,'float32','ieee-le')); % Rx display field of view 

strct = setfield(strct, 'rdb_hdr_fatwater', fread(fid,1,'int16','ieee-le')); % for Fat and Water Dual Recon 
strct = setfield(strct, 'rdb_hdr_fiestamlf', fread(fid,1,'int16','ieee-le')); % MFO FIESTA recon control bit 16bits   

strct = setfield(strct, 'rdb_hdr_app', fread(fid,1,'int16','ieee-le')); % Auto Post-Processing opcode 
strct = setfield(strct, 'rdb_hdr_rhncoilsel', fread(fid,1,'int16','ieee-le')); % Auto-Ncoil 
strct = setfield(strct, 'rdb_hdr_rhncoillimit', fread(fid,1,'int16','ieee-le')); % Auto-Ncoil 
strct = setfield(strct, 'rdb_hdr_app_option', fread(fid,1,'int16','ieee-le')); % Auto Post_processing options 
strct = setfield(strct, 'rdb_hdr_grad_mode', fread(fid,1,'int16','ieee-le')); % Gradient mode in Gemini project 
strct = setfield(strct, 'rdb_hdr_pfile_passes', fread(fid,1,'int16','ieee-le')); % Num passes stored in a multi-pass Pfile (0 means 1 pass) 

%    /* ASSET MRIge67407 */
strct = setfield(strct, 'rdb_hdr_asset', fread(fid,1,'int32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_asset_calthresh', fread(fid,1,'int32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_asset_R', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_coilno', fread(fid,1,'int32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_asset_phases', fread(fid,1,'int32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_scancent', fread(fid,1,'float32','ieee-le')); % Table position   
strct = setfield(strct, 'rdb_hdr_position', fread(fid,1,'int32','ieee-le')); % Patient position 
strct = setfield(strct, 'rdb_hdr_entry', fread(fid,1,'int32','ieee-le')); % Patient entry    
strct = setfield(strct, 'rdb_hdr_lmhor', fread(fid,1,'float32','ieee-le')); % Landmark         
strct = setfield(strct, 'rdb_hdr_last_slice_num', fread(fid,1,'int32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_asset_slice_R', fread(fid,1,'float32','ieee-le')); % Slice reduction factor 
strct = setfield(strct, 'rdb_hdr_asset_slabwrap', fread(fid,1,'float32','ieee-le'));

%    /* YMSmr03584 For Navigator echo phase correction on MFO2 */
strct = setfield(strct, 'rdb_hdr_dwnav_coeff', fread(fid,1,'float32','ieee-le')); % Coeff for amount of phase correction 
strct = setfield(strct, 'rdb_hdr_dwnav_cor', fread(fid,1,'int16','ieee-le')); % Navigator echo correction 
strct = setfield(strct, 'rdb_hdr_dwnav_view', fread(fid,1,'int16','ieee-le')); % Num of views of nav echoes 
strct = setfield(strct, 'rdb_hdr_dwnav_corecho', fread(fid,1,'int16','ieee-le')); % Num of nav echoes for actual correction 
strct = setfield(strct, 'rdb_hdr_dwnav_sview', fread(fid,1,'int16','ieee-le')); % Start view for phase correction process 
strct = setfield(strct, 'rdb_hdr_dwnav_eview', fread(fid,1,'int16','ieee-le')); % End view for phase correction process 
strct = setfield(strct, 'rdb_hdr_dwnav_sshot', fread(fid,1,'int16','ieee-le')); % Start shot for delta phase estimation in nav echoes 
strct = setfield(strct, 'rdb_hdr_dwnav_eshot', fread(fid,1,'int16','ieee-le')); % End shot for delta phase estimation in nav echoes 

%    /* 3D Windowing  */
strct = setfield(strct, 'rdb_hdr_3dwin_type', fread(fid,1,'int16','ieee-le')); % 0 = Modified Hanning, 1 = modified Tukey 
strct = setfield(strct, 'rdb_hdr_3dwin_apod', fread(fid,1,'float32','ieee-le')); % degree of apodization; 0.0 = boxcar, 1.0=hanning 
strct = setfield(strct, 'rdb_hdr_3dwin_q', fread(fid,1,'float32','ieee-le')); % apodization at ends, 0.0 = max, 1.0 = boxcar 

%    /* AutoSCIC++, AutoClariview and Enhanced Recon paramaters */
strct = setfield(strct, 'rdb_hdr_ime_scic_enable', fread(fid,1,'int16','ieee-le')); % Surface Coil Intensity Correction: 1 if enabled 
strct = setfield(strct, 'rdb_hdr_clariview_type', fread(fid,1,'int16','ieee-le')); % Type of Clariview/Name of Filter 
strct = setfield(strct, 'rdb_hdr_ime_scic_edge', fread(fid,1,'float32','ieee-le')); % Edge paramaters for Enhanced Recon 
strct = setfield(strct, 'rdb_hdr_ime_scic_smooth', fread(fid,1,'float32','ieee-le')); % Smooth paramaters for Enhanced Recon 
strct = setfield(strct, 'rdb_hdr_ime_scic_focus', fread(fid,1,'float32','ieee-le')); % Focus paramaters for Enhanced Recon 
strct = setfield(strct, 'rdb_hdr_clariview_edge', fread(fid,1,'float32','ieee-le')); % Edge paramaters for clariview 
strct = setfield(strct, 'rdb_hdr_clariview_smooth', fread(fid,1,'float32','ieee-le')); % Smooth paramaters for clariview 
strct = setfield(strct, 'rdb_hdr_clariview_focus', fread(fid,1,'float32','ieee-le')); % Focus paramaters for clariview 
strct = setfield(strct, 'rdb_hdr_scic_reduction', fread(fid,1,'float32','ieee-le')); % Reduction paramater for SCIC 
strct = setfield(strct, 'rdb_hdr_scic_gauss', fread(fid,1,'float32','ieee-le')); % Gauss paramater for SCIC 
strct = setfield(strct, 'rdb_hdr_scic_threshold', fread(fid,1,'float32','ieee-le')); % Threshold paramater for SCIC 


%    /*  parameters added for EC-TRICKS */
strct = setfield(strct, 'rdb_hdr_ectricks_no_regions', fread(fid,1,'int32','ieee-le')); % Total no of regions acquired by PSD 
strct = setfield(strct, 'rdb_hdr_ectricks_input_regions', fread(fid,1,'int32','ieee-le')); % Total no of input regions for reordering 

%    /* Smart Prescan */
strct = setfield(strct, 'rdb_hdr_psc_reuse', fread(fid,1,'int16','ieee-le')); % Header field for smart prescan 

%    /*  K-space blanking fields */
strct = setfield(strct, 'rdb_hdr_left_blank', fread(fid,1,'int16','ieee-le'));
strct = setfield(strct, 'rdb_hdr_right_blank', fread(fid,1,'int16','ieee-le'));

%    /*  multi-exciter support */
strct = setfield(strct, 'rdb_hdr_acquire_type', fread(fid,1,'int16','ieee-le')); % Acquire type information from CV 

strct = setfield(strct, 'rdb_hdr_retro_control', fread(fid,1,'int16','ieee-le')); %  Retrosective FSE phase correction control flag.
%                                            This flag is initilaized by the PSD. */
strct = setfield(strct, 'rdb_hdr_etl', fread(fid,1,'int16','ieee-le')); %  Added for Retrospective FSE phase correction. This
%                                            variable has the ETL value set by the user. This 
%                                            variable has a generic name, so that any other PSD who
%                                            wants to send ETL value to Recon can use this variable.
%                                         */
strct = setfield(strct, 'rdb_hdr_pcref_start', fread(fid,1,'int16','ieee-le')); % 1st view to use for dynamic EPI phase correction. 
strct = setfield(strct, 'rdb_hdr_pcref_stop', fread(fid,1,'int16','ieee-le')); % Last view to use for dynamic EPI phase correction. 
strct = setfield(strct, 'rdb_hdr_ref_skip', fread(fid,1,'int16','ieee-le')); % Number of passes to skip for dynamic EPI phase correction. 
strct = setfield(strct, 'rdb_hdr_extra_frames_top', fread(fid,1,'int16','ieee-le')); % Number of extra frames at top of K-space 
strct = setfield(strct, 'rdb_hdr_extra_frames_bot', fread(fid,1,'int16','ieee-le')); % Number of extra frames at bottom of K-space 
strct = setfield(strct, 'rdb_hdr_multiphase_type', fread(fid,1,'int16','ieee-le')); % 0 = INTERLEAVED ,  1 = SEQUENTIAL 
strct = setfield(strct, 'rdb_hdr_nphases', fread(fid,1,'int16','ieee-le')); % Number of phases in a multiphase scan 
strct = setfield(strct, 'rdb_hdr_pure', fread(fid,1,'int16','ieee-le')); % PURE flag from psd 
strct = setfield(strct, 'rdb_hdr_pure_scale', fread(fid,1,'float32','ieee-le')); % Recon scale factor ratio for cal scan 
strct = setfield(strct, 'rdb_hdr_off_data', fread(fid,1,'int32','ieee-le')); % Byte offset to start of raw data (i.e size of POOL_HEADER)   
strct = setfield(strct, 'rdb_hdr_off_per_pass', fread(fid,1,'int32','ieee-le')); % Byte offset to start of rdb_hdr_per_pass of POOL_HEADER      
strct = setfield(strct, 'rdb_hdr_off_unlock_raw', fread(fid,1,'int32','ieee-le')); % Byte offset to start of rdb_hdr_unlock_raw of POOL_HEADER    
strct = setfield(strct, 'rdb_hdr_off_data_acq_tab', fread(fid,1,'int32','ieee-le')); % Byte offset to start of rdb_hdr_data_acq_tab of POOL_HEADER  
strct = setfield(strct, 'rdb_hdr_off_nex_tab', fread(fid,1,'int32','ieee-le')); % Byte offset to start of rdb_hdr_nex_tab of POOL_HEADER       
strct = setfield(strct, 'rdb_hdr_off_nex_abort_tab', fread(fid,1,'int32','ieee-le')); % Byte offset to start of rdb_hdr_nex_abort_tab of POOL_HEADER 
strct = setfield(strct, 'rdb_hdr_off_tool', fread(fid,1,'int32','ieee-le')); % Byte offset to start of rdb_hdr_tool of POOL_HEADER          
strct = setfield(strct, 'rdb_hdr_off_exam', fread(fid,1,'int32','ieee-le')); % Byte offset to start of rdb_hdr_exam of POOL_HEADER          
strct = setfield(strct, 'rdb_hdr_off_series', fread(fid,1,'int32','ieee-le')); % Byte offset to start of rdb_hdr_series of POOL_HEADER        
strct = setfield(strct, 'rdb_hdr_off_image', fread(fid,1,'int32','ieee-le')); % Byte offset to start of rdb_hdr_image of POOL_HEADER         
strct = setfield(strct, 'rdb_hdr_off_spare_a', fread(fid,1,'int32','ieee-le')); % spare 
strct = setfield(strct, 'rdb_hdr_off_spare_b', fread(fid,1,'int32','ieee-le')); % spare 
strct = setfield(strct, 'rdb_hdr_new_wnd_level_flag', fread(fid,1,'int32','ieee-le')); % New WW/WL algo enable/disable flag 
strct = setfield(strct, 'rdb_hdr_wnd_image_hist_area', fread(fid,1,'int32','ieee-le')); % Image Area % 
strct = setfield(strct, 'rdb_hdr_wnd_high_hist', fread(fid,1,'float32','ieee-le')); % Histogram Area Top 
strct = setfield(strct, 'rdb_hdr_wnd_lower_hist', fread(fid,1,'float32','ieee-le')); % Histogram Area Bottom 
strct = setfield(strct, 'rdb_hdr_pure_filter', fread(fid,1,'int16','ieee-le')); % PURE noise reduction on=1/off=0 
strct = setfield(strct, 'rdb_hdr_cfg_pure_filter', fread(fid,1,'int16','ieee-le')); % PURE cfg file value 
strct = setfield(strct, 'rdb_hdr_cfg_pure_fit_order', fread(fid,1,'int16','ieee-le')); % PURE cfg file value 
strct = setfield(strct, 'rdb_hdr_cfg_pure_kernelsize_z', fread(fid,1,'int16','ieee-le')); % PURE cfg file value 
strct = setfield(strct, 'rdb_hdr_cfg_pure_kernelsize_xy', fread(fid,1,'int16','ieee-le')); % PURE cfg file value 
strct = setfield(strct, 'rdb_hdr_cfg_pure_weight_radius', fread(fid,1,'int16','ieee-le')); % PURE cfg file value 
strct = setfield(strct, 'rdb_hdr_cfg_pure_intensity_scale', fread(fid,1,'int16','ieee-le')); % PURE cfg file value 
strct = setfield(strct, 'rdb_hdr_cfg_pure_noise_threshold', fread(fid,1,'int16','ieee-le')); % PURE cfg file value 

%   /* MART deblurring kernel (NDG) */
strct = setfield(strct, 'rdb_hdr_wienera', fread(fid,1,'float32','ieee-le')); % NB maintain alignment of floats 
strct = setfield(strct, 'rdb_hdr_wienerb', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_wienert2', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_wieneresp', fread(fid,1,'float32','ieee-le'));
strct = setfield(strct, 'rdb_hdr_wiener', fread(fid,1,'int16','ieee-le'));
strct = setfield(strct, 'rdb_hdr_flipfilter', fread(fid,1,'int16','ieee-le'));
strct = setfield(strct, 'rdb_hdr_dbgrecon', fread(fid,1,'int16','ieee-le'));
strct = setfield(strct, 'rdb_hdr_ech2skip', fread(fid,1,'int16','ieee-le'));

strct = setfield(strct, 'rdb_hdr_tricks_type', fread(fid,1,'int32','ieee-le')); % 0 = Subtracted, 1 = Unsubtracted 

strct = setfield(strct, 'rdb_hdr_lcfiesta_phase', fread(fid,1,'float32','ieee-le')); % LC Fiesta 
strct = setfield(strct, 'rdb_hdr_lcfiesta', fread(fid,1,'int16','ieee-le')); % LC Fiesta 
strct = setfield(strct, 'rdb_hdr_herawflt', fread(fid,1,'int16','ieee-le')); % Half echo raw data filter 
strct = setfield(strct, 'rdb_hdr_herawflt_befnwin', fread(fid,1,'int16','ieee-le')); % Half echo raw data filter 
strct = setfield(strct, 'rdb_hdr_herawflt_befntran', fread(fid,1,'int16','ieee-le')); % Half echo raw data filter 
strct = setfield(strct, 'rdb_hdr_herawflt_befamp', fread(fid,1,'float32','ieee-le')); % Half echo raw data filter 
strct = setfield(strct, 'rdb_hdr_herawflt_hpfamp', fread(fid,1,'float32','ieee-le')); % Half echo raw data filter 
strct = setfield(strct, 'rdb_hdr_heover', fread(fid,1,'int16','ieee-le')); % Half echo over sampling 

strct = setfield(strct, 'rdb_hdr_pure_correction_threshold', fread(fid,1,'int16','ieee-le')); % PURE Correction threshold 

strct = setfield(strct, 'rdb_hdr_ps_autoshim_status', fread(fid,1,'int32','ieee-le'));
%          /*1 = autoshim successful, 0 = autoshim failed/smart/OFF */

strct = setfield(strct, 'rdb_hdr_excess', fread(fid,222,'int16','ieee-le')); % free space for later expansion 

fclose(fid);
