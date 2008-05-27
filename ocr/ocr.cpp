//	mplayer tv:// -tv driver=v4l:width=160:height=120:device=/dev/video1:outfmt=rgb32:noaudio -fps 3 -vf scale=80:60,format=bgr15 -vo tga

#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "../utils/dir.h"
#include "../utils/file.h"
#include <tgastore.h>
#include <brainstore.h>

using namespace std;

int main(int argc, char *argv[])
{
	// load stores
		tgastore *picstore = new tgastore;
		brainstore *bstore = new brainstore;

	// get a file and directory handle
		Dir			dirH;
		File			fileH;

	// determine home / program directory
		string homedir = getenv("HOME");
		if ( homedir.empty() ) {
			cout << "environment variable HOME not defined/detected" << endl;
			exit(0);
		}
		string progdir = homedir;	progdir.append("/.m5");
		if ( !dirH.exists(progdir) )	dirH.make(progdir);

	// load pictures
		cerr << "loading pictures" << endl;

		vector<string> tgafiles;

		dirH.listContentsFull("ocr/pics/empty_desk/", tgafiles);
		unsigned int empty_desk = tgafiles.size();
		for ( unsigned int i = 0; i < tgafiles.size(); i++ )
			picstore->load(tgafiles[i].c_str());

		tgafiles.clear();
		dirH.listContentsFull("ocr/pics/me_at_desk/", tgafiles);
		unsigned int me_at_desk = tgafiles.size();
		for ( unsigned int i = 0; i < tgafiles.size(); i++ )
			picstore->load(tgafiles[i].c_str());

		tgafiles.clear();
		dirH.listContentsFull("ocr/pics/open_door/", tgafiles);
		unsigned int open_door = tgafiles.size();
		for ( unsigned int i = 0; i < tgafiles.size(); i++ )
			picstore->load(tgafiles[i].c_str());

		tgafiles.clear();
		dirH.listContentsFull("ocr/pics/night/", tgafiles);
		unsigned int night = tgafiles.size();
		for ( unsigned int i = 0; i < tgafiles.size(); i++ )
			picstore->load(tgafiles[i].c_str());

	// upload questions & expected answers
		for ( unsigned int p = 0; p < picstore->pictures.size(); p++ )
		{
			unsigned int expect	= 0;

			if ( p < empty_desk )							expect = 0;
			else if ( p < empty_desk+me_at_desk )					expect = 1;
			else if ( p < empty_desk+me_at_desk+open_door )				expect = 2;
			else if ( p < empty_desk+me_at_desk+open_door+night )			expect = 3;

			cerr << "QUESTION PICTURE: " << p << " expects: " << expect << endl;
			bstore->setQuery(&picstore->pictures[p], expect);
		}


//exit(0);

	// create initial (loaded) brains

		cerr << "loading initial brains" << endl;
		unsigned int nbrains = 58;
		unsigned int selectbrains = 29;
		bstore->selectBrains = selectbrains;

		string loaddir = progdir;	loaddir.append("/load");

// 		vector<string> files;
// 		dirH.listContentsFull(loaddir, files);
// 		for ( unsigned int i = 0; i < selectbrains; i++ )
// 		{
// 			cout << "loading " << files[0] << endl;
// 			string content;
// 			fileH.open( files[0], content );
//  
// 			bstore->load( &content );
// 		}

	// create initial fresh brains
		unsigned int inputs = picstore->pictures[0].size() * 10;
		unsigned int outputs = 4;
		for (unsigned int i=0; i < selectbrains; i++)
			bstore->load( inputs, outputs );

	// saving parameters
		unsigned int savedCritters = 0;
		unsigned int saveCounter = 0;
		unsigned int saveEvery = 100;

		// determine and create directories
		string savedir = progdir;	savedir.append("/save");
		stringstream buf;
			buf << savedir << "/" << time(0);
		string subsavedir = buf.str();

		if ( !dirH.exists(savedir) )	dirH.make(savedir);
		if ( !dirH.exists(subsavedir) )	dirH.make(subsavedir);

	unsigned int generations = 0;
	while (1)
	{
		// process ALL pictures by all critters
	
			bstore->process( );
	
		// initialize indices
			vector<int> indices ( nbrains, 0 );
			for ( unsigned int i = 0; i < nbrains; i++ )
				indices[i] = i;
	
		// sort results
			for ( int i = nbrains; i>0; i--  )
				for ( int j = 0; j < i-1; j++  )
					if ( bstore->brainusers[indices[j]]->weightedresult > bstore->brainusers[indices[j+1]]->weightedresult )
					{
						unsigned keepI	= indices[j];
						indices[j]	= indices[j+1];
						indices[j+1]	= keepI;
					}
	
		// print out SORTED results
			generations++;
			system("clear");
			for (unsigned int i=0; i < nbrains; i++)
				cerr << "gen:" << setw(6) << generations << " brain:" << setw(4) << indices[i] << " : " << "right: " << setw(4) << bstore->brainusers[indices[i]]->results << "/" << picstore->pictures.size() << ", wrong: " << setw(3) << bstore->brainusers[indices[i]]->misses << " (N: " << setw(4) << bstore->brainusers[indices[i]]->brain.totalNeurons << " C: " << setw(5) << bstore->brainusers[indices[i]]->brain.totalSynapses << " F: " << setw(5) << bstore->brainusers[indices[i]]->brain.neuronsFired << ") " << setprecision(10) << setw(10) << bstore->brainusers[indices[i]]->weightedresult << endl;
			//cerr << endl;

		// save best Critter
			if ( ++saveCounter == saveEvery )
			{
				saveCounter = 0;
	
				string* bstring = bstore->brainusers[indices[nbrains-1]]->brain.getArch();
	
				cerr << "saving brain " << indices[nbrains-1] << endl;
	
				// determine filename
				stringstream filename;
				filename << subsavedir << "/brain-" << setfill('0') << setw(6) << savedCritters;
				string sfilename = filename.str();
	
				// save brain
				fileH.save(sfilename, bstring);
	
				savedCritters++;
			}
	
		// remove worst ones
			for ( unsigned int i=0; i < selectbrains; i++ )
			{
				//cerr << "removing " << indices[0] << endl;
				delete bstore->brainusers[indices[0]];
				bstore->brainusers.erase(bstore->brainusers.begin()+indices[0]);
	
				// adapt indices, higher ones drop one
				for ( unsigned int k=1; k < indices.size(); k++ )
					if ( indices[k] > indices[0] ) indices[k]--;
	
				indices.erase(indices.begin());
			}

	}


	// destruct
	delete picstore;
	delete bstore;
}
