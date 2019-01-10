using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace GUI_CS
{
    public partial class formArch : Form
    {
        public formArch()
        {
            InitializeComponent();
        }     
        private static StringBuilder archOut = null;
        private static StringBuilder archErr = null;
        private static int numOutputLines = 0;
        private void btnProcess_Click(object sender, EventArgs e)
        {
            string cmd = comboBoxCmd.Text;
            openFDialog.Multiselect = false;
            if (cmd == "-a")
            {
                if (saveFDialog.ShowDialog() == DialogResult.OK) 
                {
                    if (saveFDialog.CheckPathExists)
                    {
                        openFDialog.Multiselect = true;
                        openFDialog.Title = "Determin files to be archiched";
                        if (openFDialog.ShowDialog() == DialogResult.OK)
                        {
                            if (openFDialog.CheckFileExists)
                            {
                                cmd += @" """; cmd += saveFDialog.FileName; cmd += @""" ";
                                foreach (string y in openFDialog.FileNames)
                                    cmd += " \"" + y + "\" ";
                            }
                            else
                            {
                                MessageBox.Show("Invalid file path.", "Try again.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                return;
                            }
                        }
                        else
                            return;
                    }
                    else
                    { 
                        MessageBox.Show("Invalid file path.", "Try again.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }
                }   
                else
                    return;
            }
            else
            if (cmd == "-v" || cmd == "-l" || cmd == "-u")
            {
                bool vcmd = (cmd == "-v");
                openFDialog.Title = "Determine archive";
                if (openFDialog.ShowDialog() == DialogResult.OK)
                {
                    cmd += " \"" + openFDialog.FileName + "\" ";
                }
                else
                    return;
                if (vcmd)
                {
                    openFDialog.Multiselect = true;
                    openFDialog.Title = "Determine files for verification";
                    if (openFDialog.ShowDialog() == DialogResult.OK)
                    {
                        if (openFDialog.CheckFileExists)
                        {
                            foreach (string y in openFDialog.FileNames)
                                cmd += " \"" + y + "\" ";
                        }
                        else
                        {
                            MessageBox.Show("Invalid file names.", "Try again.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            return;
                        }
                    }
                    else
                        return;
                }
            }
            else
            {
                MessageBox.Show("Invalid command.", "Try again.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            arch_process.StartInfo.Arguments = cmd;

            arch_process.StartInfo.RedirectStandardOutput = true;
            arch_process.StartInfo.RedirectStandardError = true;
            arch_process.StartInfo.CreateNoWindow = true;

            arch_process.Start();

            txtboxLog.AppendText(arch_process.StandardError.ReadToEnd());
            txtboxLog.AppendText(arch_process.StandardOutput.ReadToEnd());
            arch_process.Close();
        }

        private void formArch_FormClosed(object sender, FormClosedEventArgs e)
        {
            arch_process.Close();
        }
        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("• -a archivename file1 file2 ... fileN - Create an archive with the specified name from the specified files.\n• -u archivename - Unnpack files in the directory of archive \n• -l archivename - list archive files\n• -v archivename file1 file2...fileN - verify archive.\nFor extra info check README.md","Help", MessageBoxButtons.OK, MessageBoxIcon.Question);
        }
        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("VKrAr - is a C Program which has the capability to archive files,\nunpack an archive file, display data about an archive file,\nand check the validity an archive file.\nAuthor - Vladislav Krestinin Minsk, Belarus 2018.", "About", MessageBoxButtons.OK, MessageBoxIcon.Question);
        }

        private void arch_process_Exited(object sender, EventArgs e)
        {

        }
    }
}
