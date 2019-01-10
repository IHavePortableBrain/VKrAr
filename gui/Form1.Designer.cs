namespace GUI_CS
{
    partial class formArch
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(formArch));
            this.arch_process = new System.Diagnostics.Process();
            this.btnProcess = new System.Windows.Forms.Button();
            this.txtboxLog = new System.Windows.Forms.TextBox();
            this.lblCmd = new System.Windows.Forms.Label();
            this.comboBoxCmd = new System.Windows.Forms.ComboBox();
            this.saveFDialog = new System.Windows.Forms.SaveFileDialog();
            this.openFDialog = new System.Windows.Forms.OpenFileDialog();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // arch_process
            // 
            this.arch_process.StartInfo.Domain = "";
            this.arch_process.StartInfo.ErrorDialog = true;
            this.arch_process.StartInfo.FileName = "D:\\$ 3 сем\\ЯП\\Курсовая\\My\\GUi_archiver\\GUI_CS\\Debug\\archiver.exe";
            this.arch_process.StartInfo.LoadUserProfile = false;
            this.arch_process.StartInfo.Password = null;
            this.arch_process.StartInfo.RedirectStandardError = true;
            this.arch_process.StartInfo.StandardErrorEncoding = null;
            this.arch_process.StartInfo.StandardOutputEncoding = null;
            this.arch_process.StartInfo.UserName = "";
            this.arch_process.StartInfo.UseShellExecute = false;
            this.arch_process.SynchronizingObject = this;
            this.arch_process.Exited += new System.EventHandler(this.arch_process_Exited);
            // 
            // btnProcess
            // 
            this.btnProcess.Font = new System.Drawing.Font("Consolas", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnProcess.Location = new System.Drawing.Point(12, 50);
            this.btnProcess.Name = "btnProcess";
            this.btnProcess.Size = new System.Drawing.Size(459, 94);
            this.btnProcess.TabIndex = 0;
            this.btnProcess.Text = "Process";
            this.btnProcess.UseVisualStyleBackColor = true;
            this.btnProcess.Click += new System.EventHandler(this.btnProcess_Click);
            // 
            // txtboxLog
            // 
            this.txtboxLog.Font = new System.Drawing.Font("Consolas", 11.13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.txtboxLog.Location = new System.Drawing.Point(12, 164);
            this.txtboxLog.Multiline = true;
            this.txtboxLog.Name = "txtboxLog";
            this.txtboxLog.ReadOnly = true;
            this.txtboxLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtboxLog.Size = new System.Drawing.Size(776, 232);
            this.txtboxLog.TabIndex = 1;
            // 
            // lblCmd
            // 
            this.lblCmd.AutoSize = true;
            this.lblCmd.Font = new System.Drawing.Font("Consolas", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblCmd.Location = new System.Drawing.Point(528, 50);
            this.lblCmd.Name = "lblCmd";
            this.lblCmd.Size = new System.Drawing.Size(120, 26);
            this.lblCmd.TabIndex = 3;
            this.lblCmd.Text = "command: ";
            // 
            // comboBoxCmd
            // 
            this.comboBoxCmd.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
            this.comboBoxCmd.BackColor = System.Drawing.SystemColors.Window;
            this.comboBoxCmd.Font = new System.Drawing.Font("Consolas", 13.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.comboBoxCmd.FormattingEnabled = true;
            this.comboBoxCmd.Items.AddRange(new object[] {
            "-a",
            "-l",
            "-u",
            "-v"});
            this.comboBoxCmd.Location = new System.Drawing.Point(667, 50);
            this.comboBoxCmd.Name = "comboBoxCmd";
            this.comboBoxCmd.Size = new System.Drawing.Size(121, 34);
            this.comboBoxCmd.Sorted = true;
            this.comboBoxCmd.TabIndex = 4;
            this.comboBoxCmd.Text = "-a";
            // 
            // saveFDialog
            // 
            this.saveFDialog.DefaultExt = "vkr";
            this.saveFDialog.FileName = "VKrAr";
            this.saveFDialog.Filter = "VKrAr (*.vkr)|*.vkr|All files (*.*)|*.*";
            this.saveFDialog.Title = "save archive";
            // 
            // openFDialog
            // 
            this.openFDialog.Filter = "All files (*.*)|*.*|VKrAr (*.vkr)|*.vkr";
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.helpToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 28);
            this.menuStrip1.TabIndex = 5;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(53, 24);
            this.helpToolStripMenuItem.Text = "Help";
            this.helpToolStripMenuItem.Click += new System.EventHandler(this.helpToolStripMenuItem_Click);
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(62, 24);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // formArch
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.ClientSize = new System.Drawing.Size(800, 400);
            this.Controls.Add(this.comboBoxCmd);
            this.Controls.Add(this.lblCmd);
            this.Controls.Add(this.txtboxLog);
            this.Controls.Add(this.btnProcess);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "formArch";
            this.Text = "VKrAr";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.formArch_FormClosed);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Diagnostics.Process arch_process;
        private System.Windows.Forms.Button btnProcess;
        private System.Windows.Forms.TextBox txtboxLog;
        private System.Windows.Forms.ComboBox comboBoxCmd;
        private System.Windows.Forms.Label lblCmd;
        private System.Windows.Forms.SaveFileDialog saveFDialog;
        private System.Windows.Forms.OpenFileDialog openFDialog;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
    }
}

