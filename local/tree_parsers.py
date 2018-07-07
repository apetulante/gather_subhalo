#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug  1 15:48:03 2017

@author: petulaa
"""

# SIMULATION CONSTANTS
PARTICLE_MASS = 3.3e7
OMEGA_M = .250000
OMEGA_LAM = .750000
H_0 = .7
T_H = 9.78e9*(1./H_0)
GRAV_CONST = 4.483e-24


import pandas as pd
from matplotlib.patches import Circle
import matplotlib.pyplot as plt
import subprocess
import numpy as np
import os

#DONE AND WORKS!
def construct_treeDF(tree_file):
    ''' Create a dataframe from the raw data, by removing headers and comments,
    and adding appropriate column names '''
    treeDF = pd.read_csv(tree_file, delim_whitespace = True, skiprows=50, 
                         comment = '#', index_col = False, header=None,
                         names = ['scale', 'ID', 'desc_scale', 'descID', 'num_prog',
                         'pid', 'Upid', 'desc_pid', 'phantom', 'SAM_Mvir', 
                         'mvir', 'rvir', 'r_s', 'Vrms', 'mmp', 'scale_of_last_MM',
                         'Vmax', 'x', 'y', 'z', 'Vx', 'Vy', 'Vz', 'Jx', 'Jy', 'Jz'
                         'spin', 'breadth_first_ID', 'depth_first_ID', 'tree_root_ID',
                         'orig_halo_ID', 'snap_num', 'next_coprog_depthfirst_ID',
                         'last_prog_depthfirst_ID', 'last_mainleaf_depthfirst_ID',
                         'tidal_F, tidal_ID', 'r_s_klypin', 'M200b_all', 'M200b_1',
                         'M200b_2', 'M200b_3', 'M2500c', 'Xoff', 'Voff', 'spin_bull',
                         'b_to_a', 'c_to_a', 'A_x', 'A_y', 'A_z', 'T_U', 'M_pe', 'halfmass_R', 
                         'misc_54', 'misc_55', 'misc_56', 'misc_57', 'misc_58', 'misc_59', 
                         'misc_60'])
    return treeDF 




def construct_subpropDF(subprop_file):
    subpropDF = pd.read_csv(subprop_file, index_col = False, delim_whitespace = True,
                           header = None,
                           names = ['tree', 'halonum', 'subtree_entry', 'subtree_merge',
                           'ID_sub', 'initial_sub_mass', 'initial_host_mass', 'initial_sub_rvir',
                           'initial_host_rvir', 'initial_sub_conc', 'initial_host_conc',
                           'initial_sub_spin', 'initial_host_spin', 'initial_sub_spin_bull',
                           'initial_host_spin_bull', 'initial_sub_rel_vx', 'initial_sub_rel_vy',
                           'initial_sub_rel_vz', 'initial_sub_x', 'initial_host_x',
                           'initial_sub_y', 'initial_host_y', 'initial_sub_z', 'initial_host_z',
                           'initial_scale', 'initial_sub_Vmax', 'initial_sub_b_to_a', 'initial_sub_c_to_a',
                           'initial_host_b_to_a', 'initial_host_c_to_a', 
                           'initial_sub_scale_last_MM', 'initial_host_scale_last_MM',
                           'initial_num_subs','initial_max_sub_mass','initial_num_host_subs',
                           'initial_max_host_sub_mass','survives', 'final_scale', 'final_sub_mass', 
                           'final_host_mass', 'final_host_rvir',
                           'final_sub_rel_x', 'final_sub_rel_y', 'final_sub_rel_z', 'final_sub_conc',
                           'final_sub_spin', 'final_sub_spin_bull',
                           'final_sub_scale_last_MM', 'final_host_scale_last_MM',
                           'initial_sub_density_1Mpc', 'initial_sub_density_2Mpc',
                           'initial_sub_density_4Mpc', 'initial_sub_tidal_1Mpc',
                           'initial_sub_tidal_2Mpc', 'initial_sub_tidal_4Mpc'])
    subpropDF.drop_duplicates(keep='first',inplace=True)
    subpropDF = subpropDF.reset_index()
    return subpropDF




def find_surviving_subs(tree_data):
    sub_indicies = []
    for i in range(len(tree_data.scale.values)):
        if tree_data.scale.values[i] == 1.0:
            if tree_data.Upid.values[i] != 1.0:
                sub_indicies.append(i)
    return sub_indicies



                
def filter_for_mmps(tree_data):
    ''' Returns a data frame that contains entries from JUST the most massive progenitors
    of each tree.'''
    mmp_DF = []
    for i in range(len(tree_data.scale)):
        if tree_data.scale[i] == 1.0:
            main_haloID = tree_data.ID[i]
            mmp_DF.append(tree_data[i])
        if tree_data.descID[i] == main_haloID:
            if tree_data.mmp[i] == 1.0:
                main_haloID = tree_data.ID[i]
                mmp_DF.append(tree_data[i])
    return mmp_DF




def find_merging_subs(tree_data, masscut = 1):
    ''' Find all subs that merge into any of the trees in the file. Returns the indicies
    at which they merge and enter their parents, as well as the indicies of the parent at the
    time of their merging and entry. Indicies are given in terms of the entire tree file. masscut
    an optional keyword that can be applied, in units of number of particles.'''
    merging_index = []
    host_index = []
    return merging_index



def grab_sub_history(subpropDF, entry, complete_sub=False):
    ''' Grab the tree file, split it appropriately, and find the history of the sub
    and its host as it infalls. Display results as a table and output them as arrays.
    complete_sub means return the sub's entire history, not just its infall.'''
    tree_file = subpropDF.tree[entry]
    halo_num = int(subpropDF.halonum[entry])
    sub_start = int(subpropDF.subtree_merge[entry])
    survival_type = int(subpropDF.survives[entry])
    current_dir = os.getcwd()
    subprocess.call('./gather_sub.sh %d %s %d %s' %(survival_type, tree_file, halo_num, current_dir), shell=True)
    
    with open('needed_files.txt') as f:
        content = f.readlines()
    # you may also want to remove whitespace characters like `\n` at the end of each line
    content = [x.strip() for x in content] 
    fullhalo_filename = content[0]
    mainhalo_filename = content[1]
    mainhalo_data = pd.read_csv(mainhalo_filename, delim_whitespace=True, header=None,
                         index_col = False,
                         names = ['scale', 'ID', 'desc_scale', 'descID', 'num_prog',
                         'pid', 'Upid', 'desc_pid', 'phantom', 'SAM_Mvir', 
                         'mvir', 'rvir', 'r_s', 'Vrms', 'mmp', 'scale_of_last_MM',
                         'Vmax', 'x', 'y', 'z', 'Vx', 'Vy', 'Vz', 'Jx', 'Jy', 'Jz'
                         'spin', 'breadth_first_ID', 'depth_first_ID', 'tree_root_ID',
                         'orig_halo_ID', 'snap_num', 'next_coprog_depthfirst_ID',
                         'last_prog_depthfirst_ID', 'last_mainleaf_depthfirst_ID',
                         'tidal_F, tidal_ID', 'r_s_klypin', 'M200b_all', 'M200b_1',
                         'M200b_2', 'M200b_3', 'M2500c', 'Xoff', 'Voff', 'spin_bull',
                         'b_to_a', 'c_to_a', 'A_x', 'A_y', 'A_z', 'T_U', 'M_pe', 'halfmass_R', 
                         'misc_54', 'misc_55', 'misc_56', 'misc_57', 'misc_58', 'misc_59', 
                         'misc_60'])
    fullhalo_data = pd.read_csv(fullhalo_filename, delim_whitespace=True, header=None,
                          index_col=False, 
                          names = ['scale', 'ID', 'desc_scale', 'descID', 'num_prog',
                         'pid', 'Upid', 'desc_pid', 'phantom', 'SAM_Mvir', 
                         'mvir', 'rvir', 'r_s', 'Vrms', 'mmp', 'scale_of_last_MM',
                         'Vmax', 'x', 'y', 'z', 'Vx', 'Vy', 'Vz', 'Jx', 'Jy', 'Jz'
                         'spin', 'breadth_first_ID', 'depth_first_ID', 'tree_root_ID',
                         'orig_halo_ID', 'snap_num', 'next_coprog_depthfirst_ID',
                         'last_prog_depthfirst_ID', 'last_mainleaf_depthfirst_ID',
                         'tidal_F, tidal_ID', 'r_s_klypin', 'M200b_all', 'M200b_1',
                         'M200b_2', 'M200b_3', 'M2500c', 'Xoff', 'Voff', 'spin_bull',
                         'b_to_a', 'c_to_a', 'A_x', 'A_y', 'A_z', 'T_U', 'M_pe', 'halfmass_R', 
                         'misc_54', 'misc_55', 'misc_56', 'misc_57', 'misc_58', 'misc_59', 
                         'misc_60'])
    
    host_ids = mainhalo_data.ID.values
    host_start = np.int(np.where(host_ids == fullhalo_data.Upid[sub_start])[0])
    
    sub_history_complete = [fullhalo_data[sub_start:sub_start+1].values[0]]
    current_ID = fullhalo_data.ID[sub_start]
    for i in range(sub_start, len(fullhalo_data.descID)):
        if fullhalo_data.descID[i] == current_ID:
            sub_history_complete.append(fullhalo_data[i:i+1].values[0])
            current_ID = fullhalo_data.ID[i]
    
    host_history = []
    for i in range(len(sub_history_complete)):
        if sub_history_complete[i][6] == -1.0:
            break
        else:
            host = np.int(np.where(host_ids == sub_history_complete[i][6])[0])
            host_history.append(mainhalo_data[host:host+1].values[0])
            sub_history = sub_history_complete[0:i+1]
   
    host_history.append(mainhalo_data[host+1:host+2].values[0])
    sub_history = sub_history_complete[0:i+1]
    
    subprocess.call('./cleanup_sub.sh %s %d %s' %(tree_file, halo_num, current_dir), shell=True)
    
    if complete_sub == False:
        return sub_history, host_history
    
    if complete_sub == True:
        return sub_history_complete, host_history
    
    

def plot_sub_massAccretion(sub_history, entry, complete=False):
    ''' Make plots of the mass accretion history of the sub. Flag "complete" = True/False
    indicates whether to include the history BEFORE the time of entry to the host or not,
    default is False'''
    #sub_history, host_history = grab_sub_history(subpropDF, entry, complete)
    
    mass = np.array(sub_history)[:,10]
    scale = np.array(sub_history)[:,0]
    plt.plot(scale,mass)
    plt.xlabel('scale')
    plt.ylabel('mass')
    plt.title("Mass Loss in Host, Sub %d" %entry)
    
    return

    

def plot_sub_infall(sub_history, host_history, entry):
    ''' Make plots of the descent of the sub into the host. Shown as both a 3D distance
    plot and 2D projections'''
    #sub_history, host_history = find_sub_history(subpropDF, entry, complete=False)
    
    sub_scale = np.array(sub_history)[:,0]
    sub_xcoord = np.array(sub_history)[:,17]
    sub_ycoord = np.array(sub_history)[:,18]
    sub_zcoord = np.array(sub_history)[:,19]
    sub_mass = np.array(sub_history)[:,10]
    sub_rvir = np.array(sub_history)[:,11]
    
    host_xcoord = np.array(host_history)[:,17]
    host_ycoord = np.array(host_history)[:,18]
    host_zcoord = np.array(host_history)[:,19]
    host_mass = np.array(host_history)[:,10]
    host_rvir = np.array(host_history)[:,11]
    
    fig = plt.figure(figsize=(12,4))
    ax=fig.add_subplot(131)
    ax.axis("equal")
    ax2=fig.add_subplot(132)
    ax2.axis("equal")
    ax3=fig.add_subplot(133)
    ax3.axis("equal")
    
    distx = host_xcoord-sub_xcoord
    disty = host_ycoord-sub_ycoord
    distz = host_zcoord-sub_zcoord
    for i in range(len(distx)):
        if distx[i] >= 130.0/2:
            distx[i] = 130.0 - distx[i]
        if disty[i] >= 130.0/2:
            disty[i] = 130.0 - disty[i]
        if distz[i] >= 130.0/2:
            distz[i] = 130.0 - distz[i]
    
    total_dist = np.sqrt(distx**2 + disty**2 + distz**2)
    fig2 = plt.figure(figsize=(12,4))
    plt.plot(sub_scale, total_dist)
    plt.title("Relative Distance to Host Center")
    plt.xlabel("scale")
    plt.ylabel("distance (Mpc)")
    
    #create shortened arrays to plots mass points
    distx_points = distx[0::5]
    disty_points = disty[0::5]
    distz_points = distz[0::5]
    sub_mass_points = sub_mass[0::5]
    sub_rvir_points = sub_rvir[0::5]
           
    host_rvir_merges = plt.Circle((0,0),radius = (host_rvir[0]/1000), color = 'b', fill = False)
    host_rvir_enters = plt.Circle((0,0),radius = (host_rvir[-1]/1000), color = 'c', fill = False)

    ax.plot(distx,disty, 'k')
    ax.scatter(distx_points,disty_points, s=((sub_mass_points**(2.0/3.0))/10**5), color = 'k')
    ax.scatter(distx[0], disty[0], s = (sub_mass[0]**(2.0/3.0))/10**5, color = 'g')
    ax.scatter(distx[-1], disty[-1], s = (sub_mass[-1]**(2.0/3.0))/10**5, color = 'r')    
    ax.add_patch(host_rvir_merges)
    ax.add_patch(host_rvir_enters) 
    ax.set_xlim([-host_rvir[-1]/1000,host_rvir[-1]/1000])  
    ax.set_ylim([-host_rvir[-1]/1000,host_rvir[-1]/1000]) 
    ax.set_title("X-Y Projected Dist")    
    
    host_rvir_merges = plt.Circle((0,0),radius = (host_rvir[0]/1000), color = 'b', fill = False)
    host_rvir_enters = plt.Circle((0,0),radius = (host_rvir[-1]/1000), color = 'c', fill = False)
    
    ax2.plot(disty,distz, 'k')
    ax2.scatter(disty_points,distz_points, s=((sub_mass_points**(2.0/3.0))/10**5), color = 'k')
    ax2.scatter(disty[0], distz[0], s = (sub_mass[0]**(2.0/3.0))/10**5, color = 'g')
    ax2.scatter(disty[-1], distz[-1], s = (sub_mass[-1]**(2.0/3.0))/10**5, color = 'r')   
    ax2.add_patch(host_rvir_merges)
    ax2.add_patch(host_rvir_enters)
    ax2.set_xlim([-host_rvir[-1]/1000,host_rvir[-1]/1000])  
    ax2.set_ylim([-host_rvir[-1]/1000,host_rvir[-1]/1000])
    ax2.set_title("Y-Z Projected Dist")    
    
    host_rvir_merges = plt.Circle((0,0),radius = (host_rvir[0]/1000), color = 'b', fill = False)
    host_rvir_enters = plt.Circle((0,0),radius = (host_rvir[-1]/1000), color = 'c', fill = False)
    
    ax3.plot(distx,distz, 'k')  
    ax3.scatter(distx_points,distz_points, s=((sub_mass_points**(2.0/3.0))/10**5), color = 'k')
    ax3.scatter(distx[0], distz[0], s = (sub_mass[0]**(2.0/3.0))/10**5, color = 'g')
    ax3.scatter(distx[-1], distz[-1], s = (sub_mass[-1]**(2.0/3.0))/10**5, color = 'r')  
    ax3.add_patch(host_rvir_merges)
    ax3.add_patch(host_rvir_enters)
    ax3.set_xlim([-host_rvir[-1]/1000,host_rvir[-1]/1000])  
    ax3.set_ylim([-host_rvir[-1]/1000,host_rvir[-1]/1000])
    ax3.set_title("X-Z Projected Dist")    
